/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:31:11 by jaubry--          #+#    #+#             */
/*   Updated: 2024/12/11 23:48:30 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

/*
    Function that returns the pixel pos of a certain pos of the map.
*/
t_vec3	get_point_cords(t_map map, int x, int y)
{
	t_vec3	point;

	point.x = x;
	point.y = y;
	point.z = map.map[y][x].z;
	return (point);
}
