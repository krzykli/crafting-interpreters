
echo "Compiling..."
gcc -Wall -I./include main.c chunk.c memory.c debug.c -o clox
echo "Running clox"
./clox
