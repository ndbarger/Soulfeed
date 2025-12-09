#!/bin/bash

# TODO: add clean script/clean functionality in build script

# setup build directory
mkdir -pv build/obj

# build files
echo "Building files..."
gcc -c -g src/main.c -o build/obj/main.o
gcc -c -g src/error.c -o build/obj/error.o
gcc -c -g src/request.c -o build/obj/request.o
gcc -c -g src/server.c -o build/obj/server.o
gcc -c -g src/threading.c -o build/obj/threading.o
gcc -c -g src/lex.c -o build/obj/lex.o

# link files
echo "Linking files..."
gcc -g -lws2_32 build/obj/main.o build/obj/error.o build/obj/lex.o \
            build/obj/request.o build/obj/server.o build/obj/threading.o -o build/server.exe -lws2_32

#gcc -g src/main.c src/error.c src/request.c src/server.c src/threading.c -o build/server.exe -lws2_32

# finished
echo "Finished."