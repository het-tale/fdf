#include "fdf.h"
#include "gnl/get_next_line.h"

int count_lines(char *argv[])
{
    char *line;
    int count;
    int	fd;

    fd = open(argv[1], O_RDONLY);
    line = get_next_line(fd);
    count = 0;
    while (line)
    {
        line = get_next_line(fd);
        count++;
    }
    close(fd);
    return (count);
}

int count_columns(char *argv[])
{
    int removelen;
    char *line;
    char *remove;
    char **split;
    int	fd;

    fd = open(argv[1], O_RDONLY);
    removelen = 0;
    line = get_next_line(fd);
    remove = ft_strremove(line);
    split = ft_split(remove, ' ');
    while (split[removelen])
        removelen++;
    close(fd);
    return (removelen);
}

int **ft_parse_map(int count, char *argv[])
{
	char *line;
	char **split;
	int	fd;	
	int	**map;
	int	*arr;

	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	map = (int **)malloc(count * sizeof(int *));
	size_t	len = 0;
	int j = 0;
	int i = 0;
	int k = 0;
	while (line)
	{
	split = ft_split(line, ' ');
	len = 0;
	j = 0;
	i = 0;
	while (split[i])
	{
		len += ft_strlen(split[j]);
		i++;
	}
	i = 0;
	arr = (int *)malloc(len * sizeof(int));
	while (split[j])
	{
		arr[j] = ft_atoi(split[j]);
		j++;
	}
	j = 0;
	map[k] = (int *)malloc(len * sizeof(int));
	while (j < len)
	{
		map[k][j] = arr[j];
		j++;
	}
	line = get_next_line(fd);
	k++;
	}
	close(fd);
	return (map);
}
