#!/bin/bash

# TODO: add clean script/clean functionality in build script

# setup build directory
mkdir -pv build/obj

# build files
echo "Building files..."
gcc -c src/main.c -o build/obj/main.o
gcc -c src/error.c -o build/obj/error.o
gcc -c src/request.c -o build/obj/request.o
gcc -c src/server.c -o build/obj/server.o
gcc -c src/threading.c -o build/obj/threading.o
gcc -c src/lex.c -o build/obj/lex.o

# link files
echo "Linking files..."
gcc -lws2_32 build/obj/main.o build/obj/error.o build/obj/lex.o \
            build/obj/request.o build/obj/server.o build/obj/threading.o -o build/server.exe -lws2_32

#gcc -g src/main.c src/error.c src/request.c src/server.c src/threading.c -o build/server.exe -lws2_32

# finished
echo "Finished."