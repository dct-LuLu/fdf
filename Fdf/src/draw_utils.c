/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:10:14 by jaubry--          #+#    #+#             */
/*   Updated: 2024/12/11 18:10:15 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
	Function that draws a line between the current point and the
	next right and bottom one, if there's one.
*/
void	draw_segments(t_img img, t_map map, size_t x, size_t y)
{
	t_vec2	p;
	t_vec2	p1;
	t_vec2	p2;

	p = iso(fac(get_point_cords(map, x, y), map.fact));
	center(&p, map);
	if (x + 1 < map.width)
	{
		p1 = iso(fac(get_point_cords(map, x + 1, y), map.fact));
		center(&p1, map);
		ft_mlx_line_put(&img, p, p1, argb(0, 255, 0, 0));
	}
	if (y + 1 < map.height)
	{
		p2 = iso(fac(get_point_cords(map, x, y + 1), map.fact));
		center(&p2, map);
		ft_mlx_line_put(&img, p, p2, argb(0, 255, 0, 0));
	}
}

/*
	Function that draws on the image the map.
*/
void	draw_map(t_img img, t_map map)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < map.height)
	{
		x = 0;
		while (x < map.width)
		{
			draw_segments(img, map, x, y);
			x++;
		}
		y++;
	}
}
