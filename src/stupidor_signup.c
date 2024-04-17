#include "includes.h"

void stupidor_signup() {

    char username[UNAMEMAX];
    memset(username, '\0', sizeof(username));
    char password[PASSDMAX];
    memset(password, '\0', sizeof(password));
    
    /* enter username */
    printf("Enter username: ");
    fgets(username, UNAMEMAX, stdin);
    /* flush stdin */
    { int c; while ((c = getchar()) != '\n' && c != EOF) {} }

    /* enter password */
    printf("Enter password: ");
    fgets(password, PASSDMAX, stdin);
    /* flush stdin */
    { int c; while ((c = getchar()) != '\n' && c != EOF) {} }

    /* check if username is already taken */
    if (check_username(username)) {
        printf("Username already taken.\n");
        exit(EXIT_FAILURE);
    }

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
    printf("User created.\n");
    exit(EXIT_SUCCESS);
}