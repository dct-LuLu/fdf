/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   osci.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 01:04:16 by jaubry--          #+#    #+#             */
/*   Updated: 2025/02/11 16:59:20 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OSCI_H
# define OSCI_H
# ifndef DEBUG
#  define DEBUG 0
# endif
# include <pthread.h>
# include <signal.h>
# include "audio.h"
# include "mlx_utils.h"

extern pthread_mutex_t			g_stop_mutex;
extern volatile sig_atomic_t	g_stop;

typedef struct s_env
{
	t_mlx			*mlx;
	t_pa			*pa;
	int16_t			*buffer;
	size_t			buf_len;
	pthread_mutex_t	buffer_mutex;
}	t_env;

int		*init_ret(void);
int		create_threads(t_env *env, pthread_t *th_pa, pthread_t *th_mlx);
int		close_threads(pthread_t *th_pa, pthread_t *th_mlx);
void	*mlx_thread(void *arg);
void	*pa_thread(void *arg);
int		draw_routine(t_env *env);
void	handle_signal(int signal);

#endif // OSCI_H
