/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 22:13:23 by jaubry--          #+#    #+#             */
/*   Updated: 2024/12/03 04:10:38 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "libft.h"
#include "fdf.h"
#include <math.h>

#define PI 3.14159265359

void get_opposite_points(int radius, double angle, t_vec2 center, t_vec2 *a, t_vec2 *b) {
    // Point A (radius * cos(angle), radius * sin(angle))
    a->x = (int)(radius * cos(angle)) + center.x;
    a->y = (int)(radius * sin(angle)) + center.y;

    // Point B (opposite of A, i.e., angle + PI)
    b->x = (int)(radius * cos(angle + PI)) + center.x;
    b->y = (int)(radius * sin(angle + PI)) + center.y;
}

t_data	init_img(void *mlx)
{
	t_data	img;

	img.img = mlx_new_image(mlx, 2000, 2000);
	img.addr = mlx_get_data_addr(img.img, &img.byte_depth, &img.line_len, &img.endian);
	img.byte_depth /= 8;
	return (img);
}
#include <unistd.h>
int	main(void)
{
	void	*mlx;
	void	*win;
	t_data	img;//[2];
	t_vec2	a;
	t_vec2	b;
	//int	i;

	mlx = mlx_init();
	if (!mlx)
		exit(1);
	//img[0] = init_img(mlx);
	//img[1] = init_img(mlx);
	win = mlx_new_window(mlx, 2000, 2000, "feur");

	/*
	i = 0;
	double angle = 0.0;
	t_vec2	center = {1000, 1000};
	while (1)
	{
		angle += 1;
		if (angle / 100 > (2 * PI))
			angle = 0;
		img = init_img(mlx);
		get_opposite_points(2000, angle / 100, center, &a, &b);
		ft_mlx_line_put(&img, a, b, argb(0, 255, 0, 0));
		mlx_put_image_to_window(mlx, win, img.img, 0, 0);
		mlx_destroy_image(mlx, img.img);
		i = (i + 1) % 2;
	}
	*/
	int	xa = 500;
	int	ya = 500;
	int	xb = 1000;
	int	yb = 500;
	a.x = (xa * 0.866) - (ya * 0.886);
	a.y = (xa * 0.5) + (ya * 0.5);
	b.x = (xb * 0.866) - (yb * 0.866);
	b.y = (xb * 0.5) + (xa * 0.5);
	img = init_img(mlx);
	ft_mlx_line_put(&img, a, b, argb(0, 255, 0, 0));
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_destroy_image(mlx, img.img);

	//ft_printf("bits_per_pixel:%d\nbyte_depth:%d\nline_length:%d\nendian:%d\n", img.byte_depth * 8, img.byte_depth, img.line_len, img.endian);

	mlx_loop(mlx);
	return (0);
}
