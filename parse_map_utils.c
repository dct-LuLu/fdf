/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 22:40:19 by jaubry--          #+#    #+#             */
/*   Updated: 2024/12/10 02:45:24 by jaubry--         ###   ########.fr       */
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

/*
	Function to free the 2d array of ints (the map)
*/
void	free_map(t_pixel **map, size_t height)
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
