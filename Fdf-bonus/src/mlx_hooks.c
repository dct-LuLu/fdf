/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:32:25 by jaubry--          #+#    #+#             */
/*   Updated: 2025/02/13 02:52:10 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
	Function that kills mlx and returns.
*/
int	kill(t_env *env)
{
	free_map(env->map.map, env->map.height);
	mlx_destroy_image(env->mlx, env->img.img);
	mlx_destroy_window(env->mlx, env->win);
	mlx_destroy_display(env->mlx);
	free(env->mlx);
	exit(0);
	return (0);
}

/*
	Function that handles keyboard inputs 
	(arrows and zfac control)
*/
static int	controls(int keysym, t_env *env)
{
	if (keysym == 65361)
		env->map.pos.x += 10;
	else if (keysym == 65362)
		env->map.pos.y += 10;
	else if (keysym == 65363)
		env->map.pos.x -= 10;
	else if (keysym == 65364)
		env->map.pos.y -= 10;
	else if (keysym == 44)
		env->map.zfac += 0.1;
	else if (keysym == 46)
		env->map.zfac -= 0.1;
	else
		return (1);
	return (0);
}

/*
	Function that handles keyboard inputs 
*/
int	on_keypress(int keysym, t_env *env)
{
	if (DEBUG)
		ft_printf("keysym %d\n", keysym);
	if (keysym == 65307)
		kill(env);
	else if (keysym == 109)
	{
		if (env->map.proj == &iso)
			env->map.proj = &dim;
		else
			env->map.proj = &iso;
	}
	else if (keysym == 98)
		env->map.angle = (360 + (env->map.angle - 1)) % 360;
	else if (keysym == 110)
		env->map.angle = (env->map.angle + 1) % 360;
	else if (controls(keysym, env))
		return (0);
	set_arrange(&env->map);
	return (0);
}

/*
	Function that handles mouse inputs
*/
int	mouse_handler(int mousecode, int x, int y, t_env *env)
{
	if (DEBUG)
		ft_printf("mousecode %d\n", mousecode);
	(void)x;
	(void)y;
	if (mousecode == 4)
		env->map.space++;
	else if (mousecode == 5)
		env->map.space--;
	else
		return (0);
	set_arrange(&env->map);
	return (0);
}
