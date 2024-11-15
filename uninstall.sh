#!/bin/bash

# INITIAL CHECKS

if [[ $EUID -ne 0 ]]; then
    echo "Uninstallation must be performed as root."
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

if [ ! -d /usr/local/src ]; then
    echo "Error: /usr/local/src directory does not exist."
    exit 1
fi

if [ ! -d "/usr/share/doc" ]; then
    echo "Error: /usr/share/doc directory does not exist."
    exit 1
fi

if [ ! -f "/usr/local/bin/stupidor" ]; then
    echo "Stupidor is not installed."
    exit 1
fi

echo "Removing Stupidor..."

rm -rfv /var/stupidor
if [ $? -ne 0 ]; then
    echo "Error: cannot remove /var/stupidor directory."
    exit 1
fi

rm -rfv /usr/share/doc/stupidor
if [ $? -ne 0 ]; then
    echo "Error: cannot remove /usr/share/doc/stupidor directory."
    exit 1
fi

rm -rfv /usr/local/src/stupidor
if [ $? -ne 0 ]; then
    echo "Error: cannot remove /usr/local/src/stupidor directory."
    exit 1
fi

rm -fv /usr/local/bin/stupidor
if [ $? -ne 0 ]; then
    echo "Error: cannot remove /usr/local/bin/stupidor."
    exit 1
fi

echo "Stupidor has been uninstalled."