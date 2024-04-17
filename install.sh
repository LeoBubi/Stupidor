#!/bin/bash

# INITIAL CHECKS

if [[ $EUID -ne 0 ]]; then
    echo "Installation must be performed as root."
    exit 1
fi

if [ ! -d "/var" ]; then
    echo "Error: /var directory does not exist."
    exit 1
fi

if [ ! -d "/usr/local/bin" ]; then
    echo "Error: /usr/local/bin directory does not exist."
    exit 1
fi

if [ ! -d "/usr/share/doc" ]; then
    echo "Error: /usr/share/doc directory does not exist."
    exit 1
fi

if [ -d "/var/stupidor" -o -f "/usr/local/bin/stupidor" ]; then
    echo "Stupidor already installed. Run 'sudo ./uninstall.sh' to uninstall it."
    exit 1
fi

# INSTALL

make
if [ $? -ne 0 ]; then
    echo "Error: make failed."
    exit 1
fi

mv stupidor /usr/local/bin
if [ $? -eq 0 ]; then
    echo "Moved stupidor to /usr/local/bin."
else
    echo "Error: cannot move stupidor to /usr/local/bin."
    exit 1
fi


mkdir /var/stupidor
if [ $? -eq 0 ]; then
    echo "Created stupidor directory under /var"
else
    echo "Error: cannot create stupidor directory."
    exit 1
fi

touch /var/stupidor/users
if [ $? -eq 0 ]; then
    echo "Created users file under /var/stupidor."
else
    echo "Error: cannot create users file."
    exit 1
fi

chmod 00600 /var/stupidor/users
if [ $? -eq 0 ]; then
    echo "Changed users file permissions to only be accessible by root."
else
    echo "Error: cannot change users file permissions."
    exit 1
fi


mkdir /usr/share/doc/stupidor
if [ $? -eq 0 ]; then
    echo "Created stupidor directory under /usr/share/doc."
else
    echo "Error: cannot create stupidor directory."
    exit 1
fi

cp doc/* /usr/share/doc/stupidor
if [ $? -eq 0 ]; then
    echo "Copied documentation to /usr/share/doc/stupidor."
else
    echo "Error: cannot copy documentation."
    exit 1
fi
