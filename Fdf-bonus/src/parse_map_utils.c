/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 22:40:19 by jaubry--          #+#    #+#             */
/*   Updated: 2025/02/06 17:33:54 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
	returns the number count, so the map width, if an error, exit
*/
size_t	get_map_width(int fd)
{
	char	*line;
	size_t	nb_count;

	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		exit(1);
	}
	nb_count = count_tokens(line, ' ');
	while (true)
	{
		free(line);
		line = get_next_line(fd);
		if (!line)
			break ;
	}
	return (free(line), close(fd), nb_count);
}

/*
	Return the number of lines, if an error, exit or returns 0
*/
size_t	get_map_height(int fd)
{
	size_t	lines;
	char	*line;

	lines = 0;
	line = NULL;
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

void	set_min_max_map(t_map *map)
{
	size_t	x;
	size_t	y;

	map->min = 0;
	map->max = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->min > map->map[y][x].z)
				map->min = map->map[y][x].z;
			if (map->max < map->map[y][x].z)
				map->max = map->map[y][x].z;
			x++;
		}
		y++;
	}
}
