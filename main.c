
#include "fdf.h"
#include "gnl/get_next_line.h"

void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;
    x += 500;
    y += 250;
    if (x < 0 || x > 1000 || y < 0 || y > 1000)
        return ;
	dst = data->addr + (y * data->ll + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

void drawline(int x1, int y1, int x2, int y2, t_mlx *mlx)
{
    int m = 2 * ( y2 - y1);
    int error = m - (x2 - x1);

    int x = x1;
    int y = y1;

    while(x < x2)
    {
        my_mlx_pixel_put(mlx, x, y, 0xFFEBC1);
        error += m;
        if (error >= 0)
        {
            y++;
            error -= 2 * (x2 - x1);
        }
        x++;
    }
}


void ddaline(int x1, int y1, int x2, int y2, t_mlx *mlx)
{
    float x,y,dx,dy,step;
    int i;
    
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
        my_mlx_pixel_put(mlx, x, y, 0xFFEBC1);
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
static void iso(int *x, int *y, int z)
{
    int previous_x;
    int previous_y;

    previous_x = *x;
    previous_y = *y;

    // *x = (previous_x - previous_y) * cos(0.523599);
    // *y = -z + (previous_x + previous_y) * sin(0.523599);
    *x = previous_x - previous_y;
    *y = (previous_y + previous_x) / 2;

}

int destroy_window(int key, t_mlx *param)
{
    if (key == 53)
    {
        mlx_destroy_window(param->mlx, param->mlx_win);
        exit(0);
    }
    
    //printf("%d\n", key);
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
    int count;
    int columns;
    int **map;
    size_t len;
    
    fd = open(argv[1], O_RDONLY);
    count = count_lines(fd);
    close(fd);
    fd = open(argv[1], O_RDONLY);
    columns = count_columns(fd);
    close(fd);
    fd = open(argv[1], O_RDONLY);
    map = (int **)malloc((count) * sizeof(int *));
    map = fill_map(fd, map);
    i = 0;
    j = 0;
    
    while (i <= columns)
    {

        while (j < count)
        {
            x2 = i;
            y2 = j;
            
            int z = 0;//map[j][i];
            //iso(&x2, &y2, z);
            ddaline(x2 * 20, y2 * 20, x2 * 20, (y2 + 1)* 20, mlx);
            j++;
        }
        j = 0;
        i++;
    }

    j = 0;
    i = 0;
    while (j <= count)
    {

        while (i < columns)
        {
            x1 = i;
            y1 = j;

            int z = 0;//map[j][i];
            ///iso(&x1, &y1, z);
            ddaline(x1 * 20, y1 * 20, (x1 + 1) * 20, y1 * 20, mlx); //i =number of columns represents the x
            i++;                                                // j =number of lines represents the y
        }
        i = 0;
        j++;
    }
    mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img, 0, 0);
    mlx_key_hook(mlx->mlx_win, destroy_window, mlx);
    mlx_hook(mlx->mlx_win, 17, 0, ft_exit, mlx);
    mlx_loop(mlx->mlx);
}