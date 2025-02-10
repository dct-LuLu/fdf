/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:28:45 by jaubry--          #+#    #+#             */
/*   Updated: 2025/02/10 21:30:18 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "osci.h"

pthread_mutex_t			stop_mutex = PTHREAD_MUTEX_INITIALIZER;
volatile sig_atomic_t	stop = 0;

void	handle_signal(int signal)
{
	(void)signal;
	pthread_mutex_lock(&stop_mutex);
	stop = 1;
	pthread_mutex_unlock(&stop_mutex);
}
