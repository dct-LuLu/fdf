/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:10:14 by jaubry--          #+#    #+#             */
/*   Updated: 2025/02/14 00:10:31 by jaubry--         ###   ########lyon.fr   */
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

	p = map.proj(arrange(get_point_cords(map, x, y), map));
	center(&p, map);
	if (x + 1 < map.width)
	{
		p1 = map.proj(arrange(get_point_cords(map, x + 1, y), map));
		center(&p1, map);
		if (map.map[y][x].color)
			ft_mlx_line_put(&img, p, p1, map.map[y][x].color);
		else
			ft_mlx_line_put(&img, p, p1, 0xFF0000);
	}
	if (y + 1 < map.height)
	{
		p2 = map.proj(arrange(get_point_cords(map, x, y + 1), map));
		center(&p2, map);
		if (map.map[y][x].color)
			ft_mlx_line_put(&img, p, p2, map.map[y][x].color);
		else
			ft_mlx_line_put(&img, p, p2, 0xFF0000);
	}
}

/*
	Function that draws on the image the map.
*/
void	draw_map(t_env env)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < env.map.height)
	{
		x = 0;
		while (x < env.map.width)
		{
			draw_segments(env.img, env.map, x, y);
			x++;
		}
		y++;
	}
}
