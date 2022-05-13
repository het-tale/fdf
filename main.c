/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 05:03:32 by het-tale          #+#    #+#             */
/*   Updated: 2022/05/13 02:28:29 by het-tale         ###   ########.fr       */
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

void ddaline(int x1, int y1, int x2, int y2, int z1,int z2, t_mlx *mlx)
{
    float x,y,dx,dy,step,iso_x,iso_y;
    int i;
    
    x1 *= 30;
    x2 *= 30;
    y1 *= 30;
    y2 *= 30;
    z1 *= 5;
    z2 *= 5;
	// get isometric cordinates
    int original_x = x1;
    x1 = x1 - y1;
    y1 = original_x + y1 - z1;
    original_x = x2;
	x2 = x2 - y2;
    y2 = original_x + y2 - z2;

    dx=abs(x2-x1);
    dy=abs(y2-y1);
    
    if(dx> dy)
        step=dx;
    else
        step=dy;
    
    dx=(x2 - x1) / step;
    dy=(y2 - y1) / step;
    
    x=x1;
    y=y1;
    
    i=1;
    while (i<=step)
    {
        //iso_x = (x - y);
        //iso_y = (y + x) - z;
	//400 and 50 to center object on screen 
	if (z1)
        	my_mlx_pixel_put(mlx, x + 400, y + 50, 0xFF0000);
	else
        	my_mlx_pixel_put(mlx, x+400, y + 50, 0xFFEBC1);
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
            if (1 && i != columns - 1)
                ddaline(x1, y1, x2, y2, map[j][i], map[j][i + 1], mlx);
            if (1 && j != lines - 1)
                ddaline(x1, y1, x3, y3, map[j][i],map[j + 1][i], mlx);
            i++;
        }
        j++;
    }
    mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img, 0, 0);
    mlx_key_hook(mlx->mlx_win, destroy_window, mlx);
    mlx_hook(mlx->mlx_win, 17, 0, ft_exit, mlx);
    mlx_loop(mlx->mlx);
}
