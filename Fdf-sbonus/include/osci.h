/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   osci.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:49:15 by jaubry--          #+#    #+#             */
/*   Updated: 2025/01/29 20:55:46 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OSCI_H
# define OSCI_H
# include "mlx_utils.h"
# include "audio_utils.h"
# include "libft.h"
# include <math.h>
# ifndef DEBUG
#  define DEBUG 0
# endif
# include <signal.h>

extern volatile sig_atomic_t	stop;

//int	kill_osci(t_env *env);

#endif
