#include "includes.h"

int check_password(const char* username, const char* password)
{
    FILE *file = fopen(USERS_FILE, "r");
    if (file == NULL) {
        printf("Error opening users file.\n");
        return 0; // behave as if the password is incorrect
    }

    char line[URECSIZ];
    while (fgets(line, sizeof(line), file) != NULL) {
        char *uname = strtok(line, ":");
        char *passd = strtok(NULL, ":");
        passd[strcspn(passd, "\n")] = '\0';
        if (strcmp(uname, username) == 0) {
            if (strcmp(passd, password) == 0) {
                fclose(file);
                return 1; // password correct
            } else {
                fclose(file);
                return 0; // password incorrect
            }
        }
    }

    fclose(file);
    return 0;
}