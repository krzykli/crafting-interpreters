echo "Compiling..."
gcc -Wall -I./include -o clox *.c
echo "Running clox"
./clox
