/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 04:13:28 by jaubry--          #+#    #+#             */
/*   Updated: 2024/12/03 07:08:07 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <fcntl.h>

typedef struct s_map {
	size_t	width;
	size_t	height;
	int		**map;

}	t_map;

t_map	init_map(char *file);

int	main(int argc, char **argv)
{
	if (argc == 2)
		init_map(argv[1]);
	return (0);
}

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
	{
		close(fd);
		exit(1);
	}
	i = 0;
	nb_count = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\n')
			nb_count++;
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

size_t	get_str_num_len(char *str)
{
	size_t	len;

	len = 0;
	while (str[len] && ft_isdigit(str[len]))
		len++;
	return (len);
}

/*
	Function that take in parameter a string, and returns as an int the
	first number it uncounters, return -1 on error or unwanted value
*/
int	set_num_segment(char *line, int *segment)
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

void	set_num_map(int fd, t_map *map)
{
	char	*line;
	size_t	h;

	h = 0;
	line = NULL;
	while (line || !h)
	{
		line = get_next_line(fd);
		if (set_num_segment(line, map->map[h]) == -1)
		{
			map_free(map->map, h);
			free(line);
			close(fd);
			exit(1);
		}
		free(line);
		h++;
	}
}

void	set_map(char *file, t_map *map)
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
		map->map[i] = malloc(sizeof(int) * map->height);
		if (!map->map[i])
			return (map_free(map->map, i), close(fd), exit(1));
		i++;
	}
	set_num_map(fd, map);
}

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
size_t	get_str_num_len(char *str)
{
	size_t	len;

	len = 0;
	while (str[len] && ft_isdigit(str[len]))
		len++;
	return (len);
}
*/

/*
	Function that take in parameter a string, and returns as an int the
	first number it uncounters, return -1 on error or unwanted value
*/
/*
int	zatoi(char *str)
{
	size_t	num_len;
	char	*str_num;
	int		num;

	num_len = get_str_num_len(str);
	if (num_len == 0)
		return (-1);
	str_num = ft_strndup(str, num_len);
	if (!str_num)
		return (-1);
	num = ratoi(str_num);
	free(str_num);
	if (num < 0)
		return (-1);
	return (num);
}

int	get_nb_count(char *line)
{
	int		nb_count;
	size_t	i;

	i = 0;
	nb_count = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\n')
			nb_count++;
		i++;
	}
	return (nb_count);
}

int	*get_num_line(char *line, int nb_count)
{
	size_t	i;
	size_t	j;
	int		*num_line;

	num_line = malloc(sizeof(int) * (nb_count + 1));
	if (!num_line)
		return (NULL);
	num_line[nb_count] = -1;
	i = 0;
	j = 0;
	while (line[i])
	{
		if (ft_isdigit(line[i]))
		{
			num_line[j] = zatoi(line + i);
			i += get_str_num_len(line + i);
			j++;
		}
		i++;
	}
	return (num_line);
}

int	**get_num_map(char *file)
{
	int		fd;
	char	*line;
	int		**map;
	size_t	i;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit(1);
	i = 0;
	while (line)
	{
		line = get_next_line(fd);
		if (line)
		{
			map[i] = get_num_line(line, get_nb_count(line));
			i++;
		}
	}
}

t_vec2	**parse_map(char *file)
{
	int		fd;
	char	*line;
	t_vec2	**vec_map;
	int		i;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit(1);
	while (line)
	{
		line = get_next_line(fd);
		i = 0;
		while (line && line[i])
		{

			i++;
		}
	}
}
*/
