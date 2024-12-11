/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 22:13:23 by jaubry--          #+#    #+#             */
/*   Updated: 2024/12/11 15:55:19 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "fdf.h"
#include <math.h>
#include <X11/X.h>
#include <X11/keysym.h>

t_img	init_img(void *mlx, int width, int height)
{
	t_img	img;

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
	point.z = map.map[y][x].z;
	return (point);
}

t_vec3	fac(t_vec3 p, int fact)
{
	p.x *= fact;
	p.y *= fact;
	p.z *= 1;
	return (p);
}

void	center(t_vec2 *p, t_map map)
{
	p->x += map.offset.x;
	p->y += map.offset.y;
}

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

void	draw_map(t_img img, t_map map)
{
	size_t	y;
	size_t	x;
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

int	kill(t_env *env)
{
	free_map(env->map.map, env->map.height);
	mlx_destroy_image(env->mlx, env->img.img);
	mlx_destroy_window(env->mlx, env->win);
	mlx_destroy_display(env->mlx);
	exit(0);
	return (0);
}

#include <unistd.h>
int	main(int argc, char **argv)
{
	t_env	env;
	int		width;
	int		height;

	if (argc == 2)
	{
		width = 1000;
		height = 1000;
		env.map = init_map(argv[1]);
		env.mlx = mlx_init();
		if (!env.mlx)
			return (free_map(env.map.map, env.map.height), 1);
		env.win = mlx_new_window(env.mlx, width, height, "fdf");
		env.img = init_img(env.mlx, width, height);
		set_fact(&env.map, env.img);
		set_offset(&env.map, env.img);	
		draw_map(env.img, env.map);
		ft_mlx_line_put(&env.img, new_vec2(0, 0), new_vec2(env.img.width, env.img.height), argb(0, 0, 255, 0));
		ft_mlx_line_put(&env.img, new_vec2(0, env.img.height), new_vec2(env.img.width, 0), argb(0, 0, 255, 0));
		mlx_put_image_to_window(env.mlx, env.win, env.img.img, 0, 0);
		mlx_hook(env.win, DestroyNotify, StructureNotifyMask, &kill, &env);
		mlx_loop(env.mlx);
	}
	return (0);
}
