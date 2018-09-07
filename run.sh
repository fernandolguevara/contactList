#!/bin/bash
# Run script

if [ ! -d "build" ]; then
    mkdir build
fi

gcc -o build/main src/main/main.c src/lib/linkedList/linkedList.c src/lib/contact/contact.c && ./build/main