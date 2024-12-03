/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 22:40:19 by jaubry--          #+#    #+#             */
/*   Updated: 2024/12/03 22:49:14 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
	returns the number count, so the map width, if an error, exit or returns 0
*/
size_t	get_map_width(char *file)
{
	size_t	nb_count;
	size_t	i;
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit(1);
	line = get_next_line(fd);
	if (!line)
		return (close(fd), exit(1), -1);
	i = 0;
	nb_count = 0;
	while (line[i])
	{
		if (ft_isdigit(line[i]) || line[i] == '-')
		{
			nb_count++;
			while (line[i] && (ft_isdigit(line[i]) || line[i] == '-'))
				i++;
		}
		i++;
	}
	return (free(line), close(fd), nb_count);
}

/*
	Return the number of lines, if an error, exit or returns 0
*/
size_t	get_map_height(char *file)
{
	size_t	lines;
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit(1);
	lines = 0;
	while (!lines || line)
	{
		line = get_next_line(fd);
		if (!line && !lines)
			return (close(fd), 0);
		if (line)
			lines++;
		free(line);
	}
	return (close(fd), lines);
}

/*
	Function that retruns the lenght of a number as string
*/
size_t	get_str_num_len(char *str)
{
	size_t	len;

	len = 0;
	while (str[len] && (ft_isdigit(str[len]) || str[len] == '-'))
		len++;
	return (len);
}

/*
	Function to free the 2d array of ints (the map)
*/
void	map_free(int **map, size_t height)
{
	size_t	h;

	h = 0;
	while (h < height)
	{
		free(map[h]);
		h++;
	}
	free(map);
}
