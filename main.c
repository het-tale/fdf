/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 05:03:32 by het-tale          #+#    #+#             */
/*   Updated: 2022/04/18 05:03:35 by het-tale         ###   ########.fr       */
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

void ddaline(int x1, int y1, int x2, int y2, t_mlx *mlx)
{
    float x,y,dx,dy,step,iso_x,iso_y;
    int i;
    
    x1 *= 30;
    x2 *= 30;
    y1 *= 30;
    y2 *= 30;
    dx=abs(x2-x1);
    dy=abs(y2-y1);
    
    if(dx>=dy)
        step=dx;
    else
        step=dy;
    
    dx=dx/step;
    dy=dy/step;
    
    x=x1;
    y=y1;
    
    i=1;
    while (i<=step)
    {
        iso_x = (x - y) + 500;
        iso_y = (y + x) / 2;
        iso_y += 250;
        my_mlx_pixel_put(mlx, iso_x, iso_y, 0xFFEBC1);
        x=x+dx;
        y=y+dy;
        i=i+1;
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

int main(int argc, char *argv[])
{
    t_mlx *mlx = init_canvas();
    int fd;
    char *line;
    int j;
    int i;
    int x1;
    int y1;
    int x2;
    int y2;
    int x3;
    int y3;
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
            x1 = i;
            y1 = j;
            x2 = i + 1;
            y2 = j;
            x3 = i;
            y3 = j + 1;
            if (i != columns - 1)
                ddaline(x1, y1, x2, y2, mlx);
            if (j != lines - 1)
                ddaline(x1, y1, x3, y3, mlx);
            i++;
        }
        j++;
    }
    mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img, 0, 0);
    mlx_key_hook(mlx->mlx_win, destroy_window, mlx);
    mlx_hook(mlx->mlx_win, 17, 0, ft_exit, mlx);
    mlx_loop(mlx->mlx);
}
