# `stupidor` vulnerability

Once we obtained local access to the server, we first check what user we're logged in as:


```
$ whoami
karen
```

We then check if we have sudo rights:

```
$ sudo -l
[sudo] password for karen: 
Sorry, user karen may not run sudo on ubuntu-server
```

We also check the groups of which we're a member:

```
$ id
uid=1001(karen) gid=1001(karen) groups=1001(karen)
```

Well, this user is quite useless... or is it? We look around the user's direcotries and find a file `reminder.txt` in the Desktop. Let's read it:

```
$ cat reminder.txt 
April 23, 2024

Η ημερομηνία κυκλοφορίας του Stupidor είναι τον Ιούλιο, οπότε έχω ακόμα χρόνο. 
Τέλος πάντων, πρέπει να θυμηθώ να ελέγξω ξανά τα εισερχόμενα. Λένε ότι είναι 
ευάλωτο, αν και δεν καταλαβαίνω πώς. Δεν ξέρω, θα το δω εν ευθέτω χρόνω.
```

D:

Ok, let's try translating this:

*The release date for Stupidor is in July, so I still have time. Anyway, I need to remember to check my inbox again. They say it's vulnerable, though I don't understand how. I don't know, I'll look into it in due course.*

Seems like they're talking about some software called Stupidor. Their inbox what? Is it bad translation? Anyway, I like the 'vulnerable' word. Maybe this has something to do with Stupidor.
