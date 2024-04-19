#ifndef DEFINES_H
#define DEFINES_H


#include "sha256.h"


void print_file(const char* filename);
int check_username(const char* username);
long long generate_seed(void);
char* get_hash(const char *input, long long seed);
int check_password(const char* username, const char* password);
void stupidor_signup(void);
void stupidor_inbox(int delete);
void stupidor_send(void);


#define UNAMEMAX  256
#define PASSDMAX  256
#define PASSHASH SHA256_BLOCK_SIZE * 2 + 1
#define MSGMAX   512

#define USERS_FILE "/var/stupidor/.users"
#define URECSIZ (UNAMEMAX+PASSHASH+13) // 13 = : + 10-digit seed + : + \n

#define DOC_DIR "/usr/share/doc/stupidor/"



#endif /* DEFINES_H */