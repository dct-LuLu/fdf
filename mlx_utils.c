/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 01:06:14 by jaubry--          #+#    #+#             */
/*   Updated: 2024/12/10 06:02:57 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_mlx_batch_put(t_data *data, t_vec2 pos, t_vec2 size, int color)
{
	int				x;
	int				y;
	int				offset;
	unsigned int	*pixels;

	offset = ((pos.y * data->line_len) + (pos.x * data->byte_depth));
	pixels = (unsigned int *)(data->addr + offset);

	x = 0;
	while (x < size.x)
	{
		y = 0;
		while (y < size.y)
		{
			pixels[x + y * data->line_len / data->byte_depth] = color;
			y++;
		}
		x++;
	}
}

void	ft_mlx_pixel_put(t_data *data, t_vec2 pos, int color)
{
	int	offset;

	if (pos.x >= 0 && pos.x < data->width && pos.y >= 0 && pos.y < data->height)
	{
		offset = ((pos.y * data->line_len) + (pos.x * data->byte_depth));
		*(unsigned int*)(data->addr + offset) = color;
	}
}

int	abs(int x)
{
	if (x < 0)
		return (-x);
	return (x);
}

void	ft_mlx_line_put(t_data *data, t_vec2 a, t_vec2 b, int color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs(b.x - a.x);
	dy = -abs(b.y - a.y);
	sx = (b.x > a.x) - (b.x < a.x);
	sy = (b.y > a.y) - (b.y < a.y);
	err = dx + dy;

	while (1)
	{
		//if (a.x >= 100 && a.x <= 1900 && a.y >= 100 && a.y <= 1900)
		ft_mlx_pixel_put(data, a, color);
		if ((a.x == b.x) && (a.y == b.y))
			break ;
		e2 = err * 2;
		
		if (e2 >= dy)
		{
			if (a.x == b.x)
				break ;
			err += dy;
			a.x += sx;
		}
		if (e2 <= dx)
		{
			if (a.y == b.y)
				break ;
			err += dx;
			a.y += sy;
		}
	}
}

int	argb(int a, int r, int g, int b)
{
	return (a << 24 | r << 16 | g << 8 | b);
}
