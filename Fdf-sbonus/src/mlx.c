/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 22:13:23 by jaubry--          #+#    #+#             */
/*   Updated: 2025/01/29 20:58:46 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "osci.h"

static void	debug_draw(t_env env)
{
	ft_mlx_line_put(&env.img, new_vec2(0, 0),
		new_vec2(env.img.width, env.img.height), argb(0, 0, 255, 0));
	ft_mlx_line_put(&env.img, new_vec2(0, env.img.height),
		new_vec2(env.img.width, 0), argb(0, 0, 255, 0));
}

static int	draw(t_env *env)
{
	kill_img(env->mlx, &env->img);
	env->img = init_img(env->mlx, WIDTH, HEIGHT);
	if (!env->img.img || !env->img.addr)
		exit(1);//wtf
	//draw_here;
	if (DEBUG)
		debug_draw(*env);
	mlx_put_image_to_window(env->mlx, env->win, env->img.img, 0, 0);
	return (0);
}

static int	loop(t_env *env)
{
	if (stop)
		kill_mlx(env);
	return (draw(env));
}

t_env	setup_mlx(void)
{
	t_env	env;

	env.mlx = NULL;
	env.mlx = mlx_init();
	if (!env.mlx)
    {
    	ft_dprintf(STDERR_FILENO, "error creating mlx instance\n");
        return (env);
    }
    env.win = mlx_new_window(env.mlx, WIDTH, HEIGHT, "osci");
    if (!env.win)
    {
		mlx_destroy_display(env.mlx);
		ft_dprintf(STDERR_FILENO, "error creating mlx window\n");
		return (env);
	}
	//ft_bzero(env->img, sizeof(t_img));
	env.img.img = NULL;
	env.img.addr = NULL;
	return (env);
}

int	kill_mlx(t_env *env)
{
	if (env->mlx && env->img.img)
		mlx_destroy_image(env->mlx, env->img.img);
	if (env->win && env->win)
		mlx_destroy_window(env->mlx, env->win);
	if (env->mlx)
		mlx_destroy_display(env->mlx);
	free(env->mlx);
	return (0);
}

int	mlx_hook_n_loop(t_env env)
{
	mlx_hook(env.win, DestroyNotify, StructureNotifyMask, &kill_mlx, &env);
	mlx_hook(env.win, KeyRelease, KeyReleaseMask, &on_keypress, &env);
	mlx_loop_hook(env.mlx, &loop, &env);
	mlx_loop(env.mlx);
	return (EXIT_SUCCESS);
}
