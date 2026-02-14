rm a.out
gcc "$1" "$2" -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -O2
./a.out
