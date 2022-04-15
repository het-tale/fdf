/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 23:46:35 by het-tale          #+#    #+#             */
/*   Updated: 2022/04/14 21:11:18 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl/get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include "fdf.h"
int count_lines(int fd)
{
    char *line;
    int count;

    line = get_next_line(fd);
    count = 0;
    while (line)
    {
        //printf("%s", line);
        line = get_next_line(fd);
        count++;
        //printf("%d\n", count);
    }
    return (count);
}

int count_columns(int fd)
{
    int removelen;
    char *line;
    char *remove;
    char **split;

    removelen = 0;
    line = get_next_line(fd);
    remove = ft_strremove(line);
    split = ft_split(remove, ' ');
    //removelen = ft_strlen(split[0]);
    while (split[removelen])
        removelen++;
    // while (line)
    // {
    //     //printf("%s", line);
    //     remove = ft_strremove(line);
    //     removelen = ft_strlen(remove);
    // }
    return (removelen);
}

int **fill_map(int fd, int **map)
{
    char *line;
    char *remove;
    char **split;
    int j;
    int je;
    int i;
    int atoi;
    int len;
    int *arr;
    size_t removelen;

    j = 0;
    je = 0;
    len = 0;
    i = 0;
    line = get_next_line(fd);
    // line = get_next_line(fd);
    // line = get_next_line(fd);
    // remove = ft_strremove(line);
       
    // split = ft_split(remove, ' ');
    // while (split[len])
    //     len++;
    // //printf("%d\n", len);
    // arr = (int *)malloc(len * sizeof(int));
    // while (split[j])
    // {
    //      //printf("%s\n", split[j]);
    //      atoi = ft_atoi(split[j]);
    //      arr[j] = atoi;
    //      //printf("%d\n", atoi);
    //      j++;
    // }
    // j = 0;
    // // while(j < len)
    // // {
    // //     printf("%d\n", arr[j]);
    // //     j++;
    // // }
    // while (i < len)
    //         {
    //             map[j] = (int *)malloc(len * sizeof(int));
    //             map[j][i] = arr[i];
    //             printf("%d", map[j][i]);
    //             i++;
    //         }
    
    while (line)
    {
        //printf("%s", line);
        remove = ft_strremove(line);
        //printf("%s", remove);
        split = ft_split(remove, ' ');
        len = 0;
        while (split[len])
            len++;
    //printf("%d\n", len);
        arr = (int *)malloc(len * sizeof(int));
        je = 0;
        while (split[je])
        {
         //printf("%s\n", split[j]);
         atoi = ft_atoi(split[je]);
         arr[je] = atoi;
         //printf("%d\n", atoi);
         je++;
        }
        //j = 0;
        //while(j < len)
        //{
            //printf("%d\n", arr[j]);
            map[j] = (int *)malloc(len * sizeof(int));
            i = 0;
            while (i < len)
            {
                map[j][i] = arr[i];
                //printf("%d", map[j][i]);
                i++;
            }
            //printf("\n");
            j++;
        //}
        line = get_next_line(fd);
    }
    //map[j] = 0;
    return (map);
}

// int main(int argc, char *argv[])
// {
//     int fd;
//     char *line;
//     int j;
//     int i;
//     int count;
//     int **map;
//     size_t len;
    
//     j = 0;
//     i = 0;
//     fd = open(argv[1], O_RDONLY);
//     count = count_lines(fd);
//     //printf("%d\n", count);
//     close(fd);
//     fd = open(argv[1], O_RDONLY);
//     //fd = open("gnl/42.fdf", O_RDONLY);
//     map = (int **)malloc((count) * sizeof(int *));
//     map = fill_map(fd, map);
//     printf("%d\n", map[8][17]);
//     // line = get_next_line(fd);
//     // line = get_next_line(fd);
//     // line = get_next_line(fd);
//     // printf("%s", line);
//     // while(map[j])
//     // {
//     //     len = ft_strlen(map[j]);
//     //     i = 0;
//     //     while (i < len)
//     //    {
//     //        printf("%c", map[j][i]);
//     //        i++;
//     //    }
//     //    printf("\n");
//     //    j++;
//     // }
//     //printf("%c", map[2][0]);
// }