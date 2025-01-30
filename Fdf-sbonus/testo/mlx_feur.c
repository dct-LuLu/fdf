/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_feur.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 22:13:23 by jaubry--          #+#    #+#             */
/*   Updated: 2025/01/30 02:48:17 by jaubry--         ###   ########lyon.fr   */
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
	pthread_mutex_lock(&stop_mutex);
	if (stop)
	{
		pthread_mutex_unlock(&stop_mutex);
		mlx_loop_end(env->mlx);
	}
	else
		pthread_mutex_unlock(&stop_mutex);
	kill_img(env->mlx, &env->img);
	env->img = init_img(env->mlx, WIDTH, HEIGHT);
	if (!env->img.img || !env->img.addr)
		return (1);
		//exit(1);
	if (DEBUG)
		debug_draw(*env);
	mlx_put_image_to_window(env->mlx, env->win, env->img.img, 0, 0);
	return (0);
}

void	*mlx_thread_feur(void *arg)
{
	t_env	*env;
	//int		*ret;

	env = (t_env *)arg;
	/*
	env = calloc(1, sizeof(t_env));
	if (!env)
	{
		*ret = 1;
		return (ret);
	}

	env->mlx = mlx_init();
	if (!env->mlx)
	{
		free(env);
		*ret = 1;
		return (ret);
	}
	env->win = NULL;
	env->win = mlx_new_window(env->mlx, WIDTH, HEIGHT, "osci");
	if (!env->win)
	{
		ft_dprintf(STDERR_FILENO, "aled\n");
		kill_mlx(env);
		*ret = 1;
		return (ret);
	}
	env->img.img = NULL;
	env->img.addr = NULL;
	*/


	mlx_hook(env->win, DestroyNotify, StructureNotifyMask, &kill_mlx, env);
	mlx_hook(env->win, KeyRelease, KeyReleaseMask, &on_keypress, env);
	mlx_loop_hook(env->mlx, &draw, env);
	mlx_loop(env->mlx);

	kill_mlx(env);

	//*ret = 0;
	return (NULL);
}
