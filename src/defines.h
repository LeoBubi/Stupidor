#ifndef DEFINES_H
#define DEFINES_H


#include "sha256.h"


void print_file(const char* filename);
int check_username(const char* username);
char* compute_sha256_hex(const char *input);
int check_password(const char* username, const char* password);
void stupidor_signup(void);
void stupidor_inbox(int delete);
void stupidor_send(void);


#define UNAMEMAX  32
#define PASSDMAX  32
#define PASSHASH SHA256_BLOCK_SIZE * 2 + 1
#define MSGMAX   512

#define USERS_FILE "/var/stupidor/.users"
#define URECSIZ (UNAMEMAX+PASSDMAX+2)   // +2 for ':' and '\n'

#define DOC_DIR "/usr/share/doc/stupidor/"



#endif /* DEFINES_H */