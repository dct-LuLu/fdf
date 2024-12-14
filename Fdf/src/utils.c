/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 02:17:22 by jaubry--          #+#    #+#             */
/*   Updated: 2024/12/14 20:08:49 by jaubry--         ###   ########lyon.fr   */
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

/*
	Function that compute:
	- the multiplying factor necessary for the map to be at
	a certain ration to be fully visible.
	- the offset of the center point of the map and the
	center of the window.
	- the mutltiplying factor for z-axis.
*/
void	set_arrange(t_map *map)
{
	t_vec2	map_center;

	map->space = (WIDTH - (WIDTH / 3)) / map->width;
	map_center = iso(new_vec3(map->width * map->space,
				map->height * map->space, 0));
	map->offset.x = (WIDTH / 2) - (map_center.x / 2);
	map->offset.y = (HEIGHT / 2) - (map_center.y / 2);
	if ((map->max - map->min) < 20)
		map->zfac = 2;
	else
		map->zfac = 1;
}

/*
	Function that applies the multiplying factor to the point cords
*/
t_vec3	arrange(t_vec3 p, t_map map)
{
	p.x *= map.space;
	p.y *= map.space;
	p.z *= map.zfac;
	return (p);
}

/*
	Function that center pixels positions to the center of the window.
*/
void	center(t_vec2 *p, t_map map)
{
	p->x += map.offset.x;
	p->y += map.offset.y;
}
