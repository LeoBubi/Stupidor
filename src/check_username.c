#include "includes.h"

int check_username(const char* username) {
    FILE* file = fopen(USERS_FILE, "r");
    if (file == NULL) {
        printf("Error opening users file.\n");
        return -1;
    }

    char line[URECSIZ];
    while (fgets(line, URECSIZ, file)) {
        char* token = strtok(line, ":");
        if (token != NULL && strcmp(token, username) == 0) {
            fclose(file);
            return 1; // Username found
        }
    }

    fclose(file);
    return 0; // Username not found
}