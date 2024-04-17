#ifndef DEFINES_H
#define DEFINES_H


int check_username(const char* username);
void stupidor_signup(void);


#define UNAMEMAX 32
#define PASSDMAX 32

#define USERS_FILE "/var/stupidor/users"
#define URECSIZ (UNAMEMAX+PASSDMAX+2)



#endif /* DEFINES_H */