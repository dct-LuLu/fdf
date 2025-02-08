/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pulseaudio_faders.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:42:39 by jaubry--          #+#    #+#             */
/*   Updated: 2025/02/08 03:06:28 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "audio_tests.h"
#include <signal.h>

volatile sig_atomic_t	g_stop = 0;

static void	handle_signal(int signal)
{
	(void)signal;
	g_stop = 1;
}

/*
	Mainloop that continues while no signal is sent.
*/
static void	run_mainloop(t_pa pa)
{
	while (!g_stop)
	{
		if (pa_mainloop_iterate(pa.loop, 0, NULL) < 0)
		{
			ft_dprintf(STDERR_FILENO, "Mainloop failed\n");
			break ;
		}
	}
}

/*
	Function to exit safely PulseAudio.
*/
static void	exit_pa_safe(t_pa pa)
{
	ft_printf("\nExiting program...\n");
	pa_stream_unref(pa.stream);
	pa_context_unref(pa.ctx);
	pa_mainloop_free(pa.loop);
	pthread_exit(NULL);
}

/*
	Main function that setups PulseAudio
*/
static void	*snd(void *args)
{
	t_pa	pa;

	(void)args;
	ft_bzero(&pa, sizeof(t_pa));
	pa.loop = pa_mainloop_new();
	pa.api = pa_mainloop_get_api(pa.loop);
	pa.ctx = pa_context_new(pa.api, "PulseAudio Recording Example");
	if (!pa.ctx)
	{
		ft_dprintf(STDERR_FILENO, "Failed to create PulseAudio context\n");
		return (NULL);
	}
	pa_context_set_state_callback(pa.ctx, context_state_callback, &pa);
	if (pa_context_connect(pa.ctx, NULL, PA_CONTEXT_NOAUTOSPAWN, NULL) < 0)
	{
		ft_dprintf(STDERR_FILENO,
			"Failed to connect to PulseAudio server: %s\n",
			pa_strerror(pa_context_errno(pa.ctx)));
		return (NULL);
	}
	run_mainloop(pa);
	exit_pa_safe(pa);
	return (NULL);
}

int	main(void)
{
	pthread_t	th_audio;

	signal(SIGINT, handle_signal);
	pthread_create(&th_audio, NULL, &snd, NULL);
	pthread_join(th_audio, NULL);
	return (0);
}
