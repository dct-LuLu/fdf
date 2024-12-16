/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 02:17:22 by jaubry--          #+#    #+#             */
/*   Updated: 2024/12/16 19:44:49 by jaubry--         ###   ########.fr       */
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

	if (!map->proj)
	{
		map->proj = &iso;
		map->space = (WIDTH - (WIDTH / 3)) / map->width;
		if ((map->max - map->min) < 20)
			map->zfac = 2;
		else
			map->zfac = 1;
	}
	map_center = map->proj(new_vec3(map->width * map->space,
				map->height * map->space, 0));
	map->offset.x = (WIDTH / 2) - (map_center.x / 2) + map->pos.x;
	map->offset.y = (HEIGHT / 2) - (map_center.y / 2) + map->pos.y;
}

/*
	Function that applies the multiplying factor to the point cords
*/
t_vec3	arrange(t_vec3 p, t_map map)
{
	float	radians;

	p.x *= map.space;
	p.y *= map.space;
	p.z = (int)(p.z * map.zfac);
	radians = map.angle * (M_PI / 180.0);
	p.x = (int)(p.x * cos(radians) - p.y * sin(radians));
	p.y = (int)(p.x * sin(radians) + p.y * cos(radians));
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
