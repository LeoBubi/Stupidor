/*
Check inbox

Usage:
    stupidor inbox

Flags:
    -h, --help          Show this help info
    -D, --delete-all    Delete all messages in the inbox
*/

#include "includes.h"

void stupidor_inbox(int delete)
{
    char username[UNAMEMAX];
    memset(username, '\0', UNAMEMAX);
    char password[PASSDMAX];
    memset(password, '\0', PASSDMAX);

    /* enter username */
    printf("Username: ");
    fgets(username, UNAMEMAX, stdin);
    if (username[strlen(username) - 1] == '\n') {
        username[strlen(username) - 1] = '\0'; // remove trailing newline
    } else { int c; while ((c = getchar()) != '\n' && c != EOF) {} } // flush stdin

    /* check if username exists */
    if (!check_username(username)) {
        printf("Username does not exist.\n");
        exit(EXIT_FAILURE);
    }

    /* enter password */
    printf("Password: ");
    fgets(password, PASSDMAX, stdin);
    if (password[strlen(password) - 1] == '\n') {
        password[strlen(password) - 1] = '\0'; // remove trailing newline
    } else { int c; while ((c = getchar()) != '\n' && c != EOF) {} } // flush stdin

    /* check if password is correct */
    if (!check_password(username, password)) {
        printf("Incorrect password.\n");
        exit(EXIT_FAILURE);
    }

    /* if delete == 1, empty the inbox */
    if (delete) {
        char filepath[PATH_MAX];
        snprintf(filepath, sizeof(filepath), "/var/stupidor/_%s_", username);
        FILE* user_file = fopen(filepath, "w");
        if (user_file == NULL) {
            printf("Error opening inbox.\n");
            exit(EXIT_FAILURE);
        }
        fclose(user_file);
        printf("Inbox cleared.\n");
        exit(EXIT_SUCCESS);
    }

    /* read inbox */
    char filepath[PATH_MAX];
    snprintf(filepath, sizeof(filepath), "/var/stupidor/_%s_", username);
    char command[strlen(filepath) + 10]; // 10 = "sudo cat " + '\0'
    snprintf(command, sizeof(command), "sudo cat %s", filepath);
    system(command); // yee it's so much easier to just use system() here LOL (jk) (chief says it's bad practice) (maybe he's right) (maybe he's wrong) (who knows) (not me) (i'm just a comment) (i'm not even real) (i'm just a figment of your imagination) (or am i) (dun dun dun) (ok i'll stop now) (bye)
    exit(EXIT_SUCCESS);
}