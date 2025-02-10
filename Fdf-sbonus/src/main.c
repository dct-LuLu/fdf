/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 22:13:23 by jaubry--          #+#    #+#             */
/*   Updated: 2025/02/10 21:07:45 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
	Function that initializes the env.
*/
static t_env	*init_env(void)
{
	t_env	*env;

	env = ft_calloc(1, sizeof(t_env));
	if (!env)
		return (NULL);
	env->mlx = mlx_init();
	if (!env->mlx)
		return (kill_mlx(env), NULL);
	env->win = mlx_new_window(env->mlx, WIDTH, HEIGHT, "osci");
	if (!env->win)
		return (kill_mlx(env), NULL);
	ft_bzero(&env->img, sizeof(t_img));
	env->img = init_img(env->mlx, WIDTH, HEIGHT);
	if (!env->img.img)
		return (kill_mlx(env), NULL);
	env->origin = (t_vec2){0, 0};
	env->size = (t_vec2){WIDTH, HEIGHT};
	env->half = (t_vec2){WIDTH / 2, HEIGHT / 2};
	env->quarter = (t_vec2){WIDTH / 4, HEIGHT / 4};
	env->color = DOT;
	return (env);
}

/*
	Function for the mlx_thread
*/
void	*mlx_thread(void *arg)
{
	t_env	*env;
	int		*ret;

	ret = (int *)arg;
	env = init_env();
	if (!env)
	{
		*ret = 1;
		return (ret);
	}
	mlx_hook(env->win, DestroyNotify, StructureNotifyMask, &kill_mlx, env);
	mlx_hook(env->win, KeyRelease, KeyReleaseMask, &on_keypress, env);
	mlx_loop_hook(env->mlx, &draw_routine, env);
	mlx_loop(env->mlx);
	kill_mlx(env);
	*ret = 0;
	return (ret);
}
