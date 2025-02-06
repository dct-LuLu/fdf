/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 22:13:23 by jaubry--          #+#    #+#             */
/*   Updated: 2025/02/06 18:23:35 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
	Function for debug purposes, that draws two diagonals, to see the center.
*/
static void	debug_draw(t_env env)
{
	ft_mlx_line_put(&env.img, new_vec2(0, 0),
		new_vec2(env.img.width, env.img.height), 0x00FF00);
	ft_mlx_line_put(&env.img, new_vec2(0, env.img.height),
		new_vec2(env.img.width, 0), 0x00FF00);
}

/*
	Routine function that handles the drawing and clearing of the screen
*/
static int	draw_routine(t_env *env)
{
	ft_mlx_batch_put(&env->img, env->origin, env->size, 0);
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
		env.size = (t_vec2){WIDTH, HEIGHT};
		env.origin = (t_vec2){0, 0};
		env.map = init_map(argv[1]);
		env.mlx = mlx_init();
		if (!env.mlx)
			return (free_map(env.map.map, env.map.height), 1);
		env.win = mlx_new_window(env.mlx, WIDTH, HEIGHT, "fdf-bonus");
		env.img = init_img(env.mlx, WIDTH, HEIGHT);
		set_arrange(&env.map);
		mlx_mouse_hook(env.win, &mouse_handler, &env);
		mlx_hook(env.win, DestroyNotify, StructureNotifyMask, &kill, &env);
		mlx_hook(env.win, KeyPress, KeyPressMask, &on_keypress, &env);
		mlx_loop_hook(env.mlx, &draw_routine, &env);
		mlx_loop(env.mlx);
	}
	return (0);
}
