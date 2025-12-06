# setup build directory
mkdir -pv build/obj

# build files
echo "Building files..."
gcc -c src/main.c -o build/obj/main.o
gcc -c src/error.c -o build/obj/error.o
gcc -c src/request.c -o build/obj/request.o
gcc -c src/server.c -o build/obj/server.o
gcc -c src/threading.c -o build/obj/threading.o

# link files
echo "Linking files..."
gcc -o build/server.exe -luser32 -lgdi32 -lws2_32 build/obj/main.o build/obj/error.o \
                        build/obj/request.o build/obj/server.o build/obj/threading.o

# finished
echo "Finished."