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
        char *seed  = strtok(NULL, ":");
        char *passd = strtok(NULL, ":");

        /* convert seed to long long */
        long long seed_ll = atoll(seed);

        passd[strcspn(passd, "\n")] = '\0';
        if (strcmp(uname, username) == 0) {
            char* hash = get_hash(password, seed_ll);
            if (strcmp(passd, hash) == 0) {
                free(hash);
                fclose(file);
                return 1; // password correct
            } else {
                free(hash);
                fclose(file);
                return 0; // password incorrect
            }
        }
    }

    fclose(file);
    return 0;
}