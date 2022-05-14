/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 05:03:32 by het-tale          #+#    #+#             */
/*   Updated: 2022/05/14 03:09:35 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "gnl/get_next_line.h"

void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;
    //to edit
    // if (x < 0 || x > 2499 || y < 0 || y > 2499)
    //     return ;
    if (x < 0 || x > data->win_width - 1 || y < 0 || y > data->win_height - 1)
        return ;
	dst = data->addr + (y * data->ll + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}
void    isometric(int *x, int *y, int z)
{
        int original_x = *x;
        *x = *x - *y;
        *y = ((original_x + *y) / 2) - z;
}

static void iso(int *x, int *y, int z)
{
    int previous_x;
    int previous_y;

    previous_x = *x;
    previous_y = *y;
    *x = (previous_x - previous_y) * cos(0.523599);
    *y = -z + (previous_x + previous_y) * sin(0.523599);
}

void ddaline(t_point p1, t_point p2, t_mlx *mlx)
{
    float x,y,dx,dy,step,iso_x,iso_y;
    int i;
    
	// get isometric cordinates
    isometric(&p1.x, &p1.y, p1.z);
    isometric(&p2.x, &p2.y, p2.z);

    dx=abs(p2.x-p1.x);
    dy=abs(p2.y-p1.y);
    
    if(dx> dy)
        step=dx;
    else
        step=dy;
    
    dx=(p2.x - p1.x) / step;
    dy=(p2.y - p1.y) / step;
    
    x=p1.x;
    y=p1.y;
    
    i=1;
    while (i<=step)
    {
	//400 and 50 to center object on screen 
    // to edit
	if (p1.z != 0 || p2.z != 0)
        my_mlx_pixel_put(mlx, x + (mlx->win_width / 2) , y + (mlx->win_height / 10), 0xFF0000);
	else
        my_mlx_pixel_put(mlx, x + (mlx->win_width / 2), y + (mlx->win_height / 10), 0xFFEBC1);
    x += dx;
    y += dy;
    i++;
    }
}
void get_window_coordinates(int *win_width, int *win_height, t_map *map)
{
    if (map->columns < 100 || map->lines < 100)
    {
        *win_width = (map->columns) * 40;
        *win_height = (map->lines) * 30;
    }
    else
    {
        *win_width = (map->columns) * 5;
        *win_height = (map->lines) * 5;
    }
}

t_mlx	*init_canvas(t_map *map)
{
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx));
	mlx->mlx = mlx_init();
    //to edit the bigger the map the bigger the window
    get_window_coordinates(&mlx->win_width, &mlx->win_height, map);
	//mlx->mlx_win = mlx_new_window(mlx->mlx, 800, 400, "FDF");
    mlx->mlx_win = mlx_new_window(mlx->mlx, mlx->win_width, mlx->win_height, "FDF");

    //mlx->img = mlx_new_image(mlx->mlx, 800, 400);
    mlx->img = mlx_new_image(mlx->mlx, mlx->win_width, mlx->win_height);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->ll, &mlx->end);
	return (mlx);
}

int destroy_window(int key, t_mlx *param)
{
    if (key == 53)
    {
        mlx_destroy_window(param->mlx, param->mlx_win);
        exit(0);
    }
    return (0);
}

int    ft_exit()
{
    exit(0);
}

t_point init_point(int i, int j, int k, t_mlx *mlx)
{
    t_point p1;
//to edit the bigger the map the smaller the scale
if (mlx->win_height > 1000 || mlx->win_height > 1000)
{
    p1.x = i * (mlx->win_width / (mlx->win_width / 2));
    p1.y = j * (mlx->win_height / (mlx->win_height / 2));
    p1.z = k;
}
else
{
    p1.x = i * (mlx->win_width / (mlx->win_width / 2)) * 10;
    p1.y = j * (mlx->win_height / (mlx->win_height / 2)) * 10;
    p1.z = k;
}
    return (p1);
}
t_map *init_map(char *argv[])
{
    t_map *map = malloc(sizeof(t_map));

    map->lines = count_lines(argv);
    map->columns = count_columns(argv);
    return(map);
}
void draw(char *argv[], t_mlx *mlx)
{
    int j;
    int i;
    int lines;
    int columns;
    int **map;
    
    lines = count_lines(argv);
    map = ft_parse_map(lines, argv);
    columns = count_columns(argv);
    j = 0;
    
        while (j < lines)
        {
            i = 0;
            while (i < columns)
            {
                if (i != columns - 1)
                    ddaline(init_point(i, j, map[j][i], mlx), init_point(i + 1, j, map[j][i + 1], mlx), mlx);
                if (j != lines - 1)
                    ddaline(init_point(i, j, map[j][i], mlx), init_point(i, j + 1, map[j + 1][i], mlx), mlx);
                i++;
            }
        j++;
    }
}

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        t_map *map = init_map(argv);
        t_mlx *mlx = init_canvas(map);
        draw(argv, mlx);
        
        mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img, 0, 0);
        mlx_key_hook(mlx->mlx_win, destroy_window, mlx);
        mlx_hook(mlx->mlx_win, 17, 0, ft_exit, mlx);
        mlx_loop(mlx->mlx);
    }
}
