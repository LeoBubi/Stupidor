#ifndef DEFINES_H
#define DEFINES_H


#include "sha256.h"


/**
 * @brief Print the contents of a file.
 * @param filename The name of the file to print.
*/
void print_file(const char* filename);

/**
 * @brief Check if the username is taken.
 * @param username The username to check.
 * @return 1 if the username is taken, 0 otherwise.
*/
int check_username(const char* username);

/**
 * @brief Generate a random seed.
 * @return A random seed.
*/
long long generate_seed(void);

/**
 * @brief Get the hash of the input.
 * @param input The input to hash.
 * @param seed The seed to use.
 * @return The hash of the input.
*/
char* get_hash(const char *input, long long seed);

/**
 * @brief Check if the password is correct for the given username.
 * @param username The username to check.
 * @param password The password to check.
 * @return 1 if the password is correct, 0 otherwise.
*/
int check_password(const char* username, const char* password);

/**
 * @brief Create a new user.
*/
void stupidor_signup(void);

/**
 * @brief Look or empty user's inbox.
 * @param delete If 1, empty the inbox.
*/
void stupidor_inbox(int delete);

/**
 * @brief Send a message to a user.
*/
void stupidor_send(void);


/* username minimum length */
#define UNAMEMIN  4
/* username maximum length */
#define UNAMEMAX  32
/* password minimum length */
#define PASSDMIN  8
/* password maximum length */
#define PASSDMAX  32
/* password hash length */
#define PASSHASH SHA256_BLOCK_SIZE * 2 + 1
/* message maximum length */
#define MSGMAX   512
/* users file path */
#define USERS_FILE "/var/stupidor/.users"
/* users file's record's size */
#define URECSIZ (UNAMEMAX+PASSHASH+13) // 13 = : + 10-digit seed + : + \n
/* documentation directory path */
#define DOC_DIR "/usr/share/doc/stupidor/"



#endif /* DEFINES_H */