#include "includes.h"


int main(int argc, char const *argv[])
{
    /* Check if the program is run as root */
    if (geteuid() != 0) {
        printf("This program must be run as root.\n");
        exit(EXIT_FAILURE);
    }

    /* Print help info (?) */
    if (argc == 1 || (argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0))) {
        FILE *file = fopen("/usr/local/share/doc/stupidor/stupidor.txt", "r");
        if (file == NULL) {
            printf("Failed to open help file.\n");
            exit(EXIT_FAILURE);
        }

        char line[256];
        while (fgets(line, sizeof(line), file) != NULL) {
            printf("%s", line);
        }

        fclose(file);
        exit(EXIT_SUCCESS);
    }

    /* Print version info (?) */
    if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0) {
        printf("stupidor 1.0\n");
        exit(EXIT_SUCCESS);
    }

    /* Check command */
    if      (strcmp(argv[1], "send") == 0)
        stupidor_send();
    else if (strcmp(argv[1], "inbox") == 0)
        stupidor_inbox();
    else if (strcmp(argv[1], "signup") == 0)
        stupidor_signup();
    else {
        printf("Invalid command.\n");
        exit(EXIT_FAILURE);
    }

    // never reached
}
