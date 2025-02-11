/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_thread.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 22:13:23 by jaubry--          #+#    #+#             */
/*   Updated: 2025/02/11 17:55:25 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "osci.h"

/*
	Function that initializes the mlx env.
*/
static t_mlx	*init_mlx(void)
{
	t_mlx	*mlx;

	mlx = ft_calloc(1, sizeof(t_mlx));
	if (!mlx)
		return (NULL);
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (kill_mlx(mlx), NULL);
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "osci");
	if (!mlx->win)
		return (kill_mlx(mlx), NULL);
	ft_bzero(&mlx->img, sizeof(t_img));
	mlx->img = init_img(mlx->mlx, WIDTH, HEIGHT);
	if (!mlx->img.img)
		return (kill_mlx(mlx), NULL);
	mlx->origin = (t_vec2){0, 0};
	mlx->size = (t_vec2){WIDTH, HEIGHT};
	mlx->half = (t_vec2){WIDTH / 2, HEIGHT / 2};
	mlx->quarter = (t_vec2){WIDTH / 4, HEIGHT / 4};
	mlx->color = DOT;
	mlx->ret = 0;
	return (mlx);
}

/*
	Function for the mlx_thread
*/
void	*mlx_thread(void *arg)
{
	int		*ret;
	t_env	*env;

	env = (t_env *)arg;
	ret = init_ret();
	if (!ret)
		return (NULL);
	env->mlx = init_mlx();
	if (!env->mlx)
		return (ret);
	mlx_hook(env->mlx->win, DestroyNotify, StructureNotifyMask, &kill_mlx,
		env->mlx);
	mlx_hook(env->mlx->win, KeyRelease, KeyReleaseMask, &on_keypress, env->mlx);
	mlx_loop_hook(env->mlx->mlx, &draw_routine, env);
	mlx_loop(env->mlx->mlx);
	kill_mlx(env->mlx);
	*ret = 0;
	return (ret);
}
