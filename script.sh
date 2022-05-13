gcc gnl/*.c *.c  -L /usr/local/include/ -lmlx -framework OpenGL -framework AppKit -o fdf -g3 -fsanitize=address
#./fdf ../fdf/test_maps/julia.fdf
