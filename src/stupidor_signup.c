#include "includes.h"

void stupidor_signup(void) {

    char username[UNAMEMAX];
    memset(username, '\0', UNAMEMAX);
    char password[PASSDMAX];
    memset(password, '\0', PASSDMAX);
    
    /* enter username */
    printf("Enter username: ");
    fgets(username, UNAMEMAX, stdin);
    if (username[strlen(username) - 1] == '\n') {
        username[strlen(username) - 1] = '\0'; // remove trailing newline
    } else { int c; while ((c = getchar()) != '\n' && c != EOF) {} } // flush stdin

    /* illegal characters */
    if (strchr(username, '.')  != NULL || 
        strchr(username, '/')  != NULL ||
        strchr(username, '\'') != NULL ||
        strchr(username, '\"') != NULL ||
        strchr(username, '+')  != NULL ||
        strchr(username, ':')  != NULL ||
        strchr(username, ';')  != NULL ||
        strchr(username, '*')  != NULL ||
        strchr(username, '|')  != NULL ||
        strchr(username, '>')  != NULL ||
        strchr(username, '^')  != NULL ||
        strchr(username, '$')  != NULL ||
        strchr(username, '\\') != NULL ||
        strchr(username, '(')  != NULL ||
        strchr(username, ')')  != NULL ||
        strchr(username, '[')  != NULL ||
        strchr(username, ']')  != NULL ||
        strchr(username, '{')  != NULL ||
        strchr(username, '}')  != NULL) {
        printf("Username can't contain './\'\"+:;*|>^$\\()[]{}'.\n");
        exit(EXIT_FAILURE);
    }

    /* check if username is already taken */
    if (check_username(username)) {
        printf("Username already taken.\n");
        exit(EXIT_FAILURE);
    }

    /* enter password */
    printf("Enter password: ");
    fgets(password, PASSDMAX, stdin);
    if (password[strlen(password) - 1] == '\n') {
        password[strlen(password) - 1] = '\0'; // remove trailing newline
    } else { int c; while ((c = getchar()) != '\n' && c != EOF) {} } // flush stdin

    /* generate seed */
    long long seed = generate_seed();
    if (seed == 0) {
        printf("Error generating password seed.\n");
        exit(EXIT_FAILURE);
    }

    /* get password hash */
    char* password_hash = get_hash(password, seed);
    if (password_hash == NULL) {
        printf("Error computing password hash.\n");
        exit(EXIT_FAILURE);
    }

    /* create new user */
    FILE* users_file = fopen(USERS_FILE, "a");
    if (users_file == NULL) {
        printf("Error opening users file.\n");
        free(password_hash);
        exit(EXIT_FAILURE);
    }

    if (fprintf(users_file, "%s:%lld:%s\n", username, seed, password_hash) < 0) {
        printf("Error writing to users file.\n");
        free(password_hash);
        fclose(users_file);
        exit(EXIT_FAILURE);
    }
    free(password_hash);
    fclose(users_file);

    /* create new user inbox */
    char filepath[PATH_MAX];
    snprintf(filepath, sizeof(filepath), "/var/stupidor/%s", username);
    if (access(filepath, F_OK) != 0) { // if already existent do nothing
        FILE* user_file = fopen(filepath, "w");
        if (user_file == NULL) {
            printf("Error creating user file.\n");
            exit(EXIT_FAILURE);
        }
        fclose(user_file);

        /* set file permissions to be accessible only by root */
        if (chmod(filepath, S_IRUSR | S_IWUSR) != 0) {
            printf("Error setting user file permissions.\n");
            exit(EXIT_FAILURE);
        }
    }

    printf("User created.\n");
    exit(EXIT_SUCCESS);
}
