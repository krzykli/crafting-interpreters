echo "Compiling..."
if (gcc -Wall -I./include -o clox *.c) then
    echo "Running clox"
    ./clox test_lox.lox
fi
