/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 04:13:28 by jaubry--          #+#    #+#             */
/*   Updated: 2025/02/06 18:22:29 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	populate_map(int fd, t_map *map);

/*
	Function that sets all the data for the map by """parsing""" it.
	Will exit safely at any error encountered.
*/
t_map	init_map(char *file)
{
	t_map	map;
	int		fd;

	map = (t_map){0};
	fd = check_open(file);
	map.width = get_map_width(fd);
	if (!map.width)
		exit(1);
	fd = check_open(file);
	map.height = get_map_height(fd);
	if (!map.height)
		exit(1);
	fd = check_open(file);
	populate_map(fd, &map);
	set_min_max_map(&map);
	return (map);
}

/*
	Function that takes as argument a string that can either be: 
	"465,0x464FD" or "465"
	Will determine if the pixel contain the info for both the z 
	and the color or not.
	And will assign and parse the corresponding values.
*/
static t_pixel	get_pixel(char *val)
{
	t_pixel	pixel;
	char	**split;

	pixel.z = 0;
	pixel.color = 0;
	if (!is_in(val, ','))
		pixel.z = ratoi(val);
	else
	{
		split = ft_split(val, ',');
		if (split && split[0] && split[1])
		{
			pixel.z = ratoi(split[0]);
			pixel.color = hex_to_int(format_hex(split[1]));
		}
		free_strr(split);
	}
	return (pixel);
}

/*
	Function that takes a line of pixels as a string and will
	use them to populate the map.
	If error, cleans all and exit.
*/
static void	set_pixel_line(int fd, t_map *map, char *line, int y)
{
	size_t	x;
	char	**pixels;

	x = 0;
	pixels = ft_split(line, ' ');
	if (!pixels)
	{
		close(fd);
		free(line);
		free_map(map->map, y);
		exit(1);
	}
	while (x < map->width)
	{
		map->map[y][x] = get_pixel(pixels[x]);
		x++;
	}
	free_strr(pixels);
}

/*
	Function that will parse the full map and populate
	each pixel values.
*/
static void	set_pixel_map(int fd, t_map *map)
{
	size_t	y;
	char	*line;

	y = 0;
	while (y < map->height)
	{
		line = get_next_line(fd);
		if (line)
			set_pixel_line(fd, map, line, y);
		free(line);
		y++;
	}
}

/*
	Function that will, alloc and populate the map with
	all the pixel values of the map file.
*/
static void	populate_map(int fd, t_map *map)
{
	size_t	y;

	map->map = malloc(sizeof(t_pixel *) * map->height);
	if (!map->map)
		return (close(fd), exit(1));
	y = 0;
	while (y < map->height)
	{
		map->map[y] = malloc(sizeof(t_pixel) * map->width);
		if (!map->map[y])
			return (free_map(map->map, y), close(fd), exit(1));
		y++;
	}
	set_pixel_map(fd, map);
	close(fd);
}
