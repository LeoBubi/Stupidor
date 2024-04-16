#!/bin/bash

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

if [ ! -f "/usr/local/bin/stupidor" ]; then
    echo "Stupidor is not installed."
    exit 1
fi

echo "Removing Stupidor..."

rm -rfv /var/stupidor
if [ $? -ne 0 ]; then
    echo "Error: cannot uninstall Stupidor."
    exit 1
fi

rm -fv /usr/local/bin/stupidor

echo "Stupidor has been uninstalled."