/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 22:13:23 by jaubry--          #+#    #+#             */
/*   Updated: 2024/12/12 03:41:49 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	debug_draw(t_env env)
{
	if (DEBUG)
	{
		ft_mlx_line_put(&env.img, new_vec2(0, 0),
			new_vec2(env.img.width, env.img.height), argb(0, 0, 255, 0));
		ft_mlx_line_put(&env.img, new_vec2(0, env.img.height),
			new_vec2(env.img.width, 0), argb(0, 0, 255, 0));
	}
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
		env.img = init_img(env.mlx, WIDTH, HEIGHT);
		set_fact(&env.map, env.img);
		set_offset(&env.map, env.img);
		draw_map(env.img, env.map);
		debug_draw(env);
		mlx_put_image_to_window(env.mlx, env.win, env.img.img, 0, 0);
		mlx_hook(env.win, DestroyNotify, StructureNotifyMask, &kill, &env);
		mlx_hook(env.win, KeyRelease, KeyReleaseMask, &on_keypress, &env);
		mlx_loop(env.mlx);
	}
	return (0);
}
