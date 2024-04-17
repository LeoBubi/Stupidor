#ifndef DEFINES_H
#define DEFINES_H


void print_file(const char* filename);
int check_username(const char* username);
void stupidor_signup(void);
void stupidor_inbox(void);
void stupidor_send(void);


#define UNAMEMAX 32
#define PASSDMAX 32

#define USERS_FILE "/var/stupidor/users"
#define URECSIZ (UNAMEMAX+PASSDMAX+2)   // +2 for ':' and '\n'



#endif /* DEFINES_H */