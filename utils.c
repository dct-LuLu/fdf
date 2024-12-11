/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 02:17:22 by jaubry--          #+#    #+#             */
/*   Updated: 2024/12/11 22:30:33 by jaubry--         ###   ########.fr       */
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
	Function that compute the multiplying factor necessary for the map to be at
	a certain ration to be fully visible.
*/
void	set_fact(t_map *map, t_img img)
{
	map->fact = (img.width - (img.width / 3)) / map->width;
}

/*
	Function that computes the offset of the center point of the map and the
	center of the window.
*/
void	set_offset(t_map *map, t_img img)
{
	t_vec2	map_center;

	map_center = iso(new_vec3(map->width * map->fact,
				map->height * map->fact, 0));
	ft_printf("%d %d\n", map_center.x, map_center.y);
	map->offset.x = (img.width / 2) - (map_center.x / 2);
	map->offset.y = (img.height / 2) - (map_center.y / 2);
}

/*
	Function that applies the multiplying factor to the point cords
*/
t_vec3	fac(t_vec3 p, int fact)
{
	p.x *= fact;
	p.y *= fact;
	p.z *= fact / 14;
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
