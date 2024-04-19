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

    /* if username is 'users' fail */
    if (strcmp(username, ".users") == 0) {
        printf("Invalid username.\n");
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

    /* create new user */
    FILE* users_file = fopen(USERS_FILE, "a");
    if (users_file == NULL) {
        printf("Error opening users file.\n");
        exit(EXIT_FAILURE);
    }

    if (fprintf(users_file, "%s:%s\n", username, password) < 0) {
        printf("Error writing to users file.\n");
        fclose(users_file);
        exit(EXIT_FAILURE);
    }
    fclose(users_file);

    /* create new user inbox */
    char filepath[PATH_MAX];
    snprintf(filepath, sizeof(filepath), "/var/stupidor/%s", username);
    if (access(filepath, F_OK) != 0) { // if already existent do nothing
        FILE* user_file = fopen(filepath, "w");
        if (user_file == NULL) {
            printf("Error creating user file.\n");
            fclose(users_file);
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
