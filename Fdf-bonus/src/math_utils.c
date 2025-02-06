/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:31:21 by jaubry--          #+#    #+#             */
/*   Updated: 2025/02/06 17:42:39 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
	Function that converts the rgb values into a single int
*/
int	rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

/*
	Function that returns the absolute value of an int
*/
int	abs(int x)
{
	if (x < 0)
		return (-x);
	return (x);
}

/*
	Function that takes a point in 3d space and return its
	isometric representation
*/
t_vec2	iso(t_vec3 point)
{
	t_vec2	iso;

	iso.x = (int)((point.x - point.y) * 0.866);
	iso.y = (int)((point.x + point.y) * 0.5 - point.z);
	return (iso);
}

/*
	Function that takes a point in 3d space and return its
	dimetric representation
*/
t_vec2	dim(t_vec3 point)
{
	t_vec2	dim;

	dim.x = (int)((point.x - point.y) * 0.707);
	dim.y = (int)((point.x + point.y) * 0.707 - point.z * 0.5);
	return (dim);
}
