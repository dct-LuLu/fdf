/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 04:13:28 by jaubry--          #+#    #+#             */
/*   Updated: 2024/12/03 22:55:19 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_map(char *file, t_map *map); 

/*
	Function that sets all the data for the map by """parsing""" it.
	Will exit safely at any error encountered.
*/
t_map	init_map(char *file)
{
	t_map	map;

	map.width = get_map_width(file);
	if (!map.width)
		exit(1);
	map.height = get_map_height(file);
	if (!map.height)
		exit(1);
	set_map(file, &map);
	return (map);
}

/*
// TEMPORARY !!!!!!!!!!!!!!!!!!
static void	display_map(t_map map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < map.height)
	{
		j = 0;
		while (j < map.width)
		{
			ft_printf("%d ", map.map[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_map	map;

	if (argc == 2)
	{
		map = init_map(argv[1]);
		display_map(map);
		map_free(map.map, map.height);
	}
	return (0);
}
*/

/*
	Function that take in parameter a string, and returns as an int the
	first number it uncounters, return -1 on error or unwanted value
*/
static int	set_num_segment(char *line, int *segment)
{
	size_t	num_len;
	char	*str_num;
	size_t	w;
	size_t	i;

	i = 0;
	w = 0;
	while (line[i])
	{
		if (ft_isdigit(line[i]) || (line[i] == '-'))
		{
			num_len = get_str_num_len(line + i);
			if (num_len == 0)
				return (-1);
			str_num = ft_strndup(line + i, num_len);
			if (!str_num)
				return (-1);
			segment[w] = ratoi(str_num);
			i += num_len;
			w++;
			free(str_num);
		}
		i++;
	}
	return (0);
}

static void	set_num_map(int fd, t_map *map)
{
	char	*line;
	size_t	h;

	h = 0;
	line = NULL;
	while (line || !h)
	{
		line = get_next_line(fd);
		if (line && set_num_segment(line, map->map[h]) == -1)
		{
			map_free(map->map, h);
			free(line);
			close(fd);
			exit(1);
		}
		if (line)
			free(line);
		h++;
	}
}

static void	set_map(char *file, t_map *map)
{
	int		fd;
	size_t	i;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit(1);
	map->map = malloc(sizeof(int *) * map->height);
	if (!map->map)
		return (close(fd), exit(1));
	i = 0;
	while (i < map->height)
	{
		map->map[i] = malloc(sizeof(int) * map->width);
		if (!map->map[i])
			return (map_free(map->map, i), close(fd), exit(1));
		i++;
	}
	set_num_map(fd, map);
}
