/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:31:21 by jaubry--          #+#    #+#             */
/*   Updated: 2025/02/05 19:50:50 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	abs(int x)
{
	if (x < 0)
		return (-x);
	return (x);
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
