/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:32:25 by jaubry--          #+#    #+#             */
/*   Updated: 2025/02/06 16:13:47 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
	Function that kills mlx and returns.
*/
int	kill(t_env *env)
{
	if (env)
	{
		if (env->map.map)
			free_map(env->map.map, env->map.height);
		if (env->mlx)
		{
			if (env->img.img)
				mlx_destroy_image(env->mlx, env->img.img);
			if (env->win)
				mlx_destroy_window(env->mlx, env->win);
			mlx_destroy_display(env->mlx);
			free(env->mlx);
		}
	}
	return (0);
}

int	on_keypress(int keysym, t_env *env)
{
	if (keysym == 65307)
		mlx_loop_end(env->mlx);
	return (0);
}
