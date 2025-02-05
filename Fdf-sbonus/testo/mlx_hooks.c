/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:32:25 by jaubry--          #+#    #+#             */
/*   Updated: 2025/02/05 17:36:22 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include <stdio.h>

int	kill_mlx(t_env *env)
{
	printf("\n\n--------------kill:\n");
	if (env)
	{
		if (env->mlx && env->img.img)
		{
			printf("img destroy\n");
			mlx_destroy_image(env->mlx, env->img.img);
		}
		if (env->mlx && env->win)
		{
			printf("win destroy\n");
			mlx_destroy_window(env->mlx, env->win);
		}
		if (env->mlx)
		{
			printf("mlx destroy\n");
			mlx_destroy_display(env->mlx);
			free(env->mlx);
		}
		printf("freed env\n");
		free(env);
	}
	pthread_mutex_lock(&stop_mutex);
	stop = 1;
	pthread_mutex_unlock(&stop_mutex);
	//exit(1);
	return (0);
}

int	on_keypress(int keysym, t_env *env)
{
	if (keysym == 65307)
		return (mlx_loop_end(env->mlx));
	return (0);
}
