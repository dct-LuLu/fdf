/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:31:21 by jaubry--          #+#    #+#             */
/*   Updated: 2024/12/14 20:27:20 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	argb(int a, int r, int g, int b)
{
	return (a << 24 | r << 16 | g << 8 | b);
}

int	abs(int x)
{
	if (x < 0)
		return (-x);
	return (x);
}

t_vec2	iso(t_vec3 point)
{
	t_vec2	iso;

	iso.x = (int)((point.x - point.y) * 0.866);
	iso.y = (int)((point.x + point.y) * 0.5 - point.z);
	return (iso);
}

t_vec2	dim(t_vec3 point)
{
	t_vec2	dim;

	dim.x = (int)((point.x - point.y) * 0.707);
	dim.y = (int)((point.x + point.y) * 0.707 - point.z * 0.5);
	return (dim);
}

t_line	get_line_data(t_vec2 a, t_vec2 b)
{
	t_line	line;

	line.dx = abs(b.x - a.x);
	line.dy = -abs(b.y - a.y);
	line.sx = (b.x > a.x) - (b.x < a.x);
	line.sy = (b.y > a.y) - (b.y < a.y);
	line.err = line.dx + line.dy;
	return (line);
}
