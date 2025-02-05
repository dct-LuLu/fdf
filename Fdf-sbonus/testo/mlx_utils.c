/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 01:06:14 by jaubry--          #+#    #+#             */
/*   Updated: 2025/02/05 21:38:27 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

unsigned int blend_colors(t_color base, t_color new)
{
    if (base.a == 0xFF)
        return (0xFF000000);

    unsigned int inv_a = 0xFF - base.a;
    unsigned int alpha_blend = new.a * inv_a;
    unsigned int out_a = base.a + (alpha_blend >> 8);

    if (out_a == 0)
        return (0xFF000000);

    unsigned int out_r = (base.r * base.a + new.r * (alpha_blend >> 8)) / out_a;
    unsigned int out_g = (base.g * base.a + new.g * (alpha_blend >> 8)) / out_a;
    unsigned int out_b = (base.b * base.a + new.b * (alpha_blend >> 8)) / out_a;

    return (out_a << 24) | (out_r << 16) | (out_g << 8) | out_b;
}

void	ft_mlx_batch_put(t_img *img, t_vec2 pos, t_vec2 size, t_color color)
{
	int				x;
	int				y;
	int				offset;
	unsigned int	*pixels;
	size_t			i;

	offset = ((pos.y * img->line_len) + (pos.x * img->byte_depth));
	pixels = (unsigned int *)(img->addr + offset);
	x = 0;
	while (x < size.x)
	{
		y = 0;
		while (y < size.y)
		{
			i = x + y * img->line_len / img->byte_depth;
			if (!GLASS)
				pixels[i] = blend_colors(color_argb(pixels[i]), color);
			else
				pixels[i] = int_argb(color);
			y++;
		}
		x++;

	}
}

/*
	Function that draws a pixel directly on the address of the img
	on the memory.
*/
void	ft_mlx_pixel_put(t_img *img, t_vec2 pos, int color)
{
	int	offset;

	if (pos.x >= 0 && pos.x < img->width && pos.y >= 0 && pos.y < img->height)
	{
		offset = ((pos.y * img->line_len) + (pos.x * img->byte_depth));
		*(unsigned int *)(img->addr + offset) = color;
	}
}

/*
	Function for line_put logic, to increment the current pixel draw pos.
*/
static void	incr_line(int *pos, int *err, int d, int s)
{
	*err += d;
	*pos += s;
}

/*
	Function that draws a line from point a to point b using a color.
*/
void	ft_mlx_line_put(t_img *img, t_vec2 a, t_vec2 b, int color)
{
	t_line	line;

	line = get_line_data(a, b);
	while (true)
	{
		if ((a.x >= 0) && (a.x <= img->width)
			&& (a.y >= 0) && (a.y <= img->height))
			ft_mlx_pixel_put(img, a, color);
		if ((a.x == b.x) && (a.y == b.y))
			break ;
		line.e2 = line.err * 2;
		if (line.e2 >= line.dy)
		{
			if (a.x == b.x)
				break ;
			incr_line(&a.x, &line.err, line.dy, line.sx);
		}
		if (line.e2 <= line.dx)
		{
			if (a.y == b.y)
				break ;
			incr_line(&a.y, &line.err, line.dx, line.sy);
		}
	}
}

/*
	Function to init image with given size, will init it's metadata too.
*/
t_img	init_img(void *mlx, int width, int height)
{
	t_img	img;

	if (GLASS)
		img.img = mlx_new_image(mlx, width, height);
	else
		img.img = mlx_new_image_alpha(mlx, width, height);
	img.addr = mlx_get_data_addr(img.img, &img.byte_depth,
			&img.line_len, &img.endian);
	img.byte_depth /= 8;
	img.width = width;
	img.height = height;
	return (img);
}

void	kill_img(void *mlx, t_img *img)
{
	if (img->img)
	{
		mlx_destroy_image(mlx, img->img);
		img->img = NULL;
	}
	if (img->addr)
		img->addr = NULL;
	img->byte_depth = 0;
	img->width = 0;
	img->height = 0;
}
