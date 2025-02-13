/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:19:48 by jaubry--          #+#    #+#             */
/*   Updated: 2025/02/13 00:45:58 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "osci.h"

static t_env	*init_env(void)
{
	t_env	*env;

	env = ft_calloc(1, sizeof(t_env));
	if (!env)
		return (NULL);
	env->buffer = NULL;
	env->buf_len = 0;
	return (env);
}

/*
	Function that creates the audio and mlx thread and checks for any errors.
*/
int	main(void)
{
	pthread_t	th_pa;
	pthread_t	th_mlx;
	int			error;
	t_env		*env;

	env = init_env();
	if (!env)
		return (EXIT_FAILURE);
	signal(SIGINT, handle_signal);
	if (create_threads(env, &th_pa, &th_mlx) == EXIT_SUCCESS)
		error = close_threads(&th_pa, &th_mlx);
	else
		error = 1;
	free(env);
	return (error);
}
