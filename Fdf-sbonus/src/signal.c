/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:28:45 by jaubry--          #+#    #+#             */
/*   Updated: 2025/02/11 17:56:42 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "osci.h"

pthread_mutex_t			g_stop_mutex = PTHREAD_MUTEX_INITIALIZER;
volatile sig_atomic_t	g_stop = 0;

void	handle_signal(int signal)
{
	(void)signal;
	pthread_mutex_lock(&g_stop_mutex);
	g_stop = 1;
	pthread_mutex_unlock(&g_stop_mutex);
}
