/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:47:48 by jaubry--          #+#    #+#             */
/*   Updated: 2025/02/11 16:55:32 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "osci.h"

int	create_threads(t_env *env, pthread_t *th_pa, pthread_t *th_mlx)
{
	if (pthread_create(th_pa, NULL, &pa_thread, env) != 0)
		return (EXIT_FAILURE);
	if (pthread_create(th_mlx, NULL, &mlx_thread, env) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	close_threads(pthread_t *th_pa, pthread_t *th_mlx)
{
	int	*ret_mlx;
	int	*ret_pa;
	int	error;

	if (pthread_join(*th_mlx, (void **)&ret_mlx) != 0)
		return (EXIT_FAILURE);
	if (pthread_join(*th_pa, (void **)&ret_pa) != 0)
		return (free(ret_mlx), EXIT_FAILURE);
	if (!ret_mlx || !ret_pa)
		error = EXIT_FAILURE;
	else
		error = (int)(*ret_mlx || *ret_pa);
	free(ret_mlx);
	free(ret_pa);
	return (error);
}

int	*init_ret(void)
{
	int	*ret;

	ret = malloc(sizeof(int));
	if (!ret)
		return (NULL);
	*ret = 1;
	return (ret);
}
