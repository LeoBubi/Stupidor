#include "includes.h"


int main(int argc, char const *argv[])
{
    if (setuid(0) != 0 || setgid(0) != 0) {
        printf("Error: initialization failed.\n");
        exit(EXIT_FAILURE);
    }

    /* Print help info (?) */
    if (argc == 1 || (argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0))) {
        print_file(DOC_DIR "stupidor.txt");
        exit(EXIT_SUCCESS);
    }

    /* Print version info (?) */
    if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0) {
        printf("stupidor 1.1\n");
        exit(EXIT_SUCCESS);
    }

    /* Check command */
    if      (strcmp(argv[1], "send") == 0)
    {
        if (argc == 3 && (strcmp(argv[2], "-h") == 0 || strcmp(argv[2], "--help") == 0)) {
            print_file(DOC_DIR "stupidor-send.txt");
            exit(EXIT_SUCCESS);
        }
        stupidor_send();
    }
    else if (strcmp(argv[1], "inbox") == 0)
    {
        if (argc == 3 && (strcmp(argv[2], "-h") == 0 || strcmp(argv[2], "--help") == 0)) {
            print_file(DOC_DIR "stupidor-inbox.txt");
            exit(EXIT_SUCCESS);
        }
        if (argc == 3 && (strcmp(argv[2], "-D") == 0 || strcmp(argv[2], "--delete-all") == 0)) {
            stupidor_inbox(1);
        }
        if (argc == 3) {
            printf("Invalid flag.\n");
            exit(EXIT_FAILURE);
        }
        stupidor_inbox(0);
    }
    else if (strcmp(argv[1], "signup") == 0)
    {
        if (argc == 3 && (strcmp(argv[2], "-h") == 0 || strcmp(argv[2], "--help") == 0)) {
            print_file(DOC_DIR "stupidor-signup.txt");
            exit(EXIT_SUCCESS);
        }
        stupidor_signup();
    }
    else {
        printf("Invalid command.\n");
        exit(EXIT_FAILURE);
    }

    // never reached
}
