/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:46:35 by jaubry--          #+#    #+#             */
/*   Updated: 2025/02/05 12:46:38 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "osci.h"

int	kill_osci(t_env env)
{
	/*
	if (env)
	{
	*/
	kill_mlx(env);
		if (env->pa)
			kill_audio(env->pa);
	/*	free(env);
	}*/
	return (0);
}

/*
t_env	init_osci(void)
{
	t_env	env;

	/*
	env->pa = init_pa();
	if (!env->pa)
		return (free(env), NULL);
	*/

/*	
	env = setup_mlx();
	if (!env);
		return (NULL);
		//return (kill_audio(env->pa), free(env), NULL);
	
	

	return (env);
}
*/

/*
int	main(void)
{
	t_env	*env;

	env = init_osci();
	
	//if (!env || !env->mlx || !env->win || !env->pa)
//		return (kill_osci(env), EXIT_FAILURE);
	

	//mlx_hook_n_loop(env);

	kill_osci(env);
	return (EXIT_SUCCESS);
}
*/
