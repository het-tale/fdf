gcc *.c gnl/*.c -L/usr/X11/lib /usr/X11/lib/libmlx.a -lXext -lX11 -o fdf
./fdf ../test_maps/42.fdf
