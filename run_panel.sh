rm a.out
gcc panel_demo.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -O2 -fopenmp
./a.out
