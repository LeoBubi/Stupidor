#include "includes.h"

void stupidor_send(void)
{
    char sender[UNAMEMAX];
    memset(sender, '\0', UNAMEMAX);
    char password[PASSDMAX];
    memset(password, '\0', PASSDMAX);
    char recipient[UNAMEMAX];
    memset(recipient, '\0', UNAMEMAX);
    char message[MSGMAX];
    memset(message, '\0', MSGMAX);

    /* enter sender */
    printf("Sender: ");
    fgets(sender, UNAMEMAX, stdin);
    if (sender[strlen(sender) - 1] == '\n') {
        sender[strlen(sender) - 1] = '\0'; // remove trailing newline
    } else { int c; while ((c = getchar()) != '\n' && c != EOF) {} } // flush stdin

    /* check if sender exists */
    if (!check_username(sender)) {
        printf("Sender does not exist.\n");
        exit(EXIT_FAILURE);
    }

    /* enter password */
    printf("Password: ");
    fgets(password, PASSDMAX, stdin);
    if (password[strlen(password) - 1] == '\n') {
        password[strlen(password) - 1] = '\0'; // remove trailing newline
    } else { int c; while ((c = getchar()) != '\n' && c != EOF) {} } // flush stdin

    /* check if password is correct */
    if (!check_password(sender, password)) {
        printf("Incorrect password.\n");
        exit(EXIT_FAILURE);
    }

    /* enter recipient */
    printf("Recipient: ");
    fgets(recipient, UNAMEMAX, stdin);
    if (recipient[strlen(recipient) - 1] == '\n') {
        recipient[strlen(recipient) - 1] = '\0'; // remove trailing newline
    } else { int c; while ((c = getchar()) != '\n' && c != EOF) {} } // flush stdin

    /* check if recipient exists */
    if (!check_username(recipient)) {
        printf("Recipient does not exist.\n");
        exit(EXIT_FAILURE);
    }

    /* enter message */
    printf("Message:\n");
    fgets(message, MSGMAX, stdin);
    if (message[strlen(message) - 1] == '\n') {
        message[strlen(message) - 1] = '\0'; // remove trailing newline
    } else { int c; while ((c = getchar()) != '\n' && c != EOF) {} } // flush stdin

    /* write message to recipient inbox */
    char filepath[PATH_MAX];
    snprintf(filepath, sizeof(filepath), "/var/stupidor/_%s_", recipient);
    FILE* user_file = fopen(filepath, "a");
    if (user_file == NULL) {
        printf("Error opening user file.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(user_file, "%s: %s\n", sender, message);
    fclose(user_file);

    printf("Message sent.\n");
    exit(EXIT_SUCCESS);
}