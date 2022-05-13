/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 20:09:34 by het-tale          #+#    #+#             */
/*   Updated: 2022/05/13 03:13:30 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
#include <stdio.h>
#include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <mlx.h>
# include <math.h>
# include <sys/time.h>
# include <signal.h>
# include <string.h> 

int count_lines(char *argv[]);
int **ft_parse_map(int count, char *argv[]);
int count_columns(char *argv[]);

typedef struct s_mlx
{
	void		*mlx;
	void		*mlx_win;
	void		*img;
	char		*addr;
	int			bpp;
	int			ll;
	int			end;
	char		**av;
}t_mlx;

typedef struct s_point
{
	int	x;
	int	y;
	int z;
}t_point;
#endif
