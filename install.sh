#!/bin/bash

if [[ $EUID -ne 0 ]]; then
    echo "Installation must be performed as root."
    exit 1
fi

if [ ! -d "/var" ]; then
    echo "Error: /var directory does not exist."
    exit 1
fi

if [ -d "/var/stupidor" ]; then
    echo "Stupidor already installed. Run uninstall.sh to uninstall."
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

