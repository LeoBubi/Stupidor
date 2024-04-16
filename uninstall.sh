#!/bin/bash

if [[ $EUID -ne 0 ]]; then
    echo "Uninstallation must be performed as root."
    exit 1
fi

if [ ! -d "/var" ]; then
    echo "Error: /var directory does not exist."
    exit 1
fi

if [ ! -d "/var/stupidor" ]; then
    echo "Stupidor is not installed."
    exit 1
fi

echo "Removing Stupidor..."
rm -rfv /var/stupidor
if [ $? -eq 0 ]; then
    echo "Uninstalled Stupidor."
else
    echo "Error: cannot uninstall Stupidor."
    exit 1
fi
