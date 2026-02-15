rm a.out
gcc mandelbrot.c compute_utils.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -O2 -fopenmp
./a.out
