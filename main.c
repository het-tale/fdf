/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 05:03:32 by het-tale          #+#    #+#             */
/*   Updated: 2022/05/13 03:38:39 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "gnl/get_next_line.h"

void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;
    if (x < 0 || x > 1000 || y < 0 || y > 1000)
        return ;
	dst = data->addr + (y * data->ll + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}
void    isometric(int *x, int *y, int z)
{
        int original_x = *x;
        *x = *x - *y;
        *y = original_x + *y - z;
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
	if (p1.z)
        	my_mlx_pixel_put(mlx, x + 400, y + 50, 0xFF0000);
	else
        	my_mlx_pixel_put(mlx, x+400, y + 50, 0xFFEBC1);
        x += dx;
        y += dy;
        i++;
    }
}

t_mlx	*init_canvas(void)
{
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx));
	mlx->mlx = mlx_init();
	mlx->mlx_win = mlx_new_window(mlx->mlx, 1000, 1000, "FDF");

    mlx->img = mlx_new_image(mlx->mlx, 1920, 1080);
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

t_point init_point(int i, int j, int k)
{
    t_point p1;

    p1.x = i * 30;
    p1.y = j * 30;
    p1.z = k * 5;
    return (p1);
}

void draw(char *argv[], t_mlx *mlx)
{
    int j;
    int i;
    int lines;
    int columns;
    int **map;
    
    lines = count_lines(argv);
    columns = count_columns(argv);
    map = ft_parse_map(lines, argv);
    j = 0;
        while (j < lines)
    {
        i = 0;
        while (i < columns)
        {
            if (i != columns - 1)
                ddaline(init_point(i, j, map[j][i]), init_point(i + 1, j, map[j][i + 1]), mlx);
            if (j != lines - 1)
                ddaline(init_point(i, j, map[j][i]), init_point(i, j + 1, map[j + 1][i]), mlx);
            i++;
        }
        j++;
    }
}

int main(int argc, char *argv[])
{
    t_mlx *mlx = init_canvas();
    draw(argv, mlx);
    mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img, 0, 0);
    mlx_key_hook(mlx->mlx_win, destroy_window, mlx);
    mlx_hook(mlx->mlx_win, 17, 0, ft_exit, mlx);
    mlx_loop(mlx->mlx);
}
