/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 22:13:23 by jaubry--          #+#    #+#             */
/*   Updated: 2024/12/14 19:43:47 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	debug_draw(t_env env)
{
	ft_mlx_line_put(&env.img, new_vec2(0, 0),
		new_vec2(env.img.width, env.img.height), argb(0, 0, 255, 0));
	ft_mlx_line_put(&env.img, new_vec2(0, env.img.height),
		new_vec2(env.img.width, 0), argb(0, 0, 255, 0));
}

int	draw(t_env *env)
{
	kill_img(env->mlx, &env->img);
	env->img = init_img(env->mlx, WIDTH, HEIGHT);
	if (!env->img.img || !env->img.addr)
		exit(1);
	draw_map(*env);
	if (DEBUG)
		debug_draw(*env);
	mlx_put_image_to_window(env->mlx, env->win, env->img.img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_env	env;

	if (argc == 2)
	{
		env.map = init_map(argv[1]);
		env.mlx = mlx_init();
		if (!env.mlx)
			return (free_map(env.map.map, env.map.height), 1);
		env.win = mlx_new_window(env.mlx, WIDTH, HEIGHT, "fdf");
		env.img.img = NULL;
		env.img.addr = NULL;
		set_space(&env.map);// to mv
		set_offset(&env.map);
		mlx_hook(env.win, DestroyNotify, StructureNotifyMask, &kill, &env);
		mlx_hook(env.win, KeyRelease, KeyReleaseMask, &on_keypress, &env);
		mlx_loop_hook(env.mlx, &draw, &env);
		mlx_loop(env.mlx);
	}
	return (0);
}
