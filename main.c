/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 22:13:23 by jaubry--          #+#    #+#             */
/*   Updated: 2024/12/06 14:10:12 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "fdf.h"
#include <math.h>

t_data	init_img(void *mlx, int width, int height)
{
	t_data	img;

	img.img = mlx_new_image(mlx, width, height);
	img.addr = mlx_get_data_addr(img.img, &img.byte_depth, &img.line_len, &img.endian);
	img.byte_depth /= 8;
	img.width = width;
	img.height = height;
	return (img);
}

t_vec2	iso(t_vec3 point)
{
	t_vec2	iso;

	iso.x = (int)((point.x - point.y) * 0.866);
	iso.y = (int)((point.x + point.y) * 0.5 - point.z);
	return (iso);
}

t_vec3	get_point_cords(t_map map, int x, int y)
{
	t_vec3	point;

	point.x = x;
	point.y = y;
	point.z = map.map[y][x];
	return (point);
}

t_vec3	fac(t_vec3 p, int fac)
{
	p.x *= fac;
	p.x += 800;
	p.y *= fac;
	p.z *= 2;
	return (p);
}

void	draw_segments(t_data img, t_map map, int x, int y)
{
	t_vec2	p;
	t_vec2	p1;
	t_vec2	p2;
	int		fact;

	fact = 8;
	p = iso(fac(get_point_cords(map, x, y), fact));
	if (x + 1 < map.width)
	{
		p1 = iso(fac(get_point_cords(map, x + 1, y), fact));
		ft_mlx_line_put(&img, p, p1, argb(0, 255, 0, 0));
	}
	if (y + 1 < map.height)
	{
		p2 = iso(fac(get_point_cords(map, x, y + 1), fact));
		ft_mlx_line_put(&img, p, p2, argb(0, 255, 0, 0));
	}
}

void	draw_map(t_data img, t_map map)
{
	int	y;
	int	x;
	//t_vec3	pos;

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

#include <unistd.h>
int	main(int argc, char **argv)
{
	void	*mlx;
	void	*win;
	t_data	img;
	t_map	map;
	int		width;
	int		height;

	if (argc == 2)
	{
		width = 2000;
		height = 2000;
		map = init_map(argv[1]);
		mlx = mlx_init();
		if (!mlx) //clear map too
			exit(1);
		win = mlx_new_window(mlx, width, height, "feur");
		img = init_img(mlx, width, height);
	
		draw_map(img, map);
		mlx_put_image_to_window(mlx, win, img.img, 0, 0);
		//mlx_destroy_image(mlx, img.img);

		mlx_loop(mlx);
	}
	return (0);
}
