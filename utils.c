/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 02:17:22 by jaubry--          #+#    #+#             */
/*   Updated: 2024/12/10 05:53:50 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>

/*
	Small utility function to check open error, and exit if error.
	/!\ Is only used before allocating anything. /!\
*/
int	check_open(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit(1);
	return (fd);
}


void	set_fact(t_map *map, t_data img)
{
	map->fact = (img.width - (img.width / 3)) / map->width;
}

void	set_offset(t_map *map, t_data img)
{
	t_vec2	map_center;

	map_center = iso(new_vec3(map->width * map->fact, map->height * map->fact, 0));
	ft_printf("%d %d\n", map_center.x, map_center.y);
	map->offset.x = (img.width / 2) - (map_center.x / 2);
	map->offset.y = (img.height / 2) - (map_center.y / 2);
}

