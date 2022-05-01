/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:29:00 by het-tale          #+#    #+#             */
/*   Updated: 2022/04/17 15:49:19 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strremove(const char *s1)
{
	// char	*s2;
	// size_t	len;
	// int		i;

	// len = ft_strlen(s1);
	// s2 = (char *)malloc((len + 1) * sizeof(char));
	// if (!s2)
	// 	return (0);
	// i = 0;
	// while (s1[i] != '\0')
	// {
	// 	s2[i] = s1[i];
	// 	i++;
	// }
	// s2[i] = '\0';
	// return (s2);

	char	*s2;
	size_t	len;
	int		i;
	int		j;

	len = ft_strlen(s1);
	s2 = (char *)malloc((len + 1) * sizeof(char));
	if (!s2)
		return (0);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		// while (s1[i] != '\0' && s1[i] == ' ')
        //     i++;
		if (s1[i] == '\n')
		{
			break ;
		}
		s2[j] = s1[i];
		if (s1[i] != '\0')
			i++;
		j++;
	}
	s2[j] = '\0';
	return (s2);
}
