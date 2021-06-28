echo "Compiling..."
if (clang -MJ data.json -Wall -I./include -o clox *.c) then
    echo "Running clox"
    ./clox test_lox.lox
fi
sed -e '1s/^/[\'$'\n''/' -e '$s/,$/\'$'\n'']/' data.json > compile_commands.json
rm data.json
