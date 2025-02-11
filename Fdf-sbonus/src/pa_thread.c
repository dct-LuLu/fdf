/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:42:39 by jaubry--          #+#    #+#             */
/*   Updated: 2025/02/11 17:29:01 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "osci.h"

/*
	Function that safely close PulseAudio instance.
*/
static void	kill_pa(t_pa *pa)
{
	if (pa && pa->loop)
	{
		ft_printf("Exiting program...\n");
		if (pa->stream)
		{
			pa_stream_unref(pa->stream);
			if (pa->ctx)
			{
				pa_context_unref(pa->ctx);
				pa_threaded_mainloop_stop(pa->loop);
			}
		}
		pa_threaded_mainloop_free(pa->loop);
	}
	if (pa)
		free(pa);
}

static void	run_mainloop(t_pa *pa)
{
	bool	in;

	in = true;
	while (in)
	{
		pa_threaded_mainloop_lock(pa->loop);
		pa_threaded_mainloop_wait(pa->loop);
		pthread_mutex_lock(&g_stop_mutex);
		if (g_stop)
		{
			ft_dprintf(STDERR_FILENO, "Quitting audio loop\n");
			in = false;
		}
		pthread_mutex_unlock(&g_stop_mutex);
		pa_threaded_mainloop_unlock(pa->loop);
	}
}

static t_pa	*init_pa(void)
{
	t_pa	*pa;

	pa = ft_calloc(1, sizeof(t_pa));
	if (!pa)
		return (NULL);
	pa->loop = pa_threaded_mainloop_new();
	if (!pa->loop)
	{
		ft_dprintf(STDERR_FILENO, "Failed to create PulseAudio mainloop\n");
		return (kill_pa(pa), NULL);
	}
	pa->api = pa_threaded_mainloop_get_api(pa->loop);
	if (!pa->api)
	{
		ft_dprintf(STDERR_FILENO, "Failed to setup PulseAudio API\n");
		return (kill_pa(pa), NULL);
	}
	pa->ctx = pa_context_new(pa->api, "PulseAudio Recording");
	if (!pa->ctx)
	{
		ft_dprintf(STDERR_FILENO, "Failed to create PulseAudio context\n");
		return (kill_pa(pa), NULL);
	}
	return (pa);
}

void	*pa_thread(void *args)
{
	t_env	*env;
	int		*ret;
	int		on;

	env = (t_env *)args;
	ret = init_ret();
	if (!ret)
		return (NULL);
	env->pa = init_pa();
	pa_context_set_state_callback(env->pa->ctx, context_state_callback, env);
	on = pa_context_connect(env->pa->ctx, NULL, PA_CONTEXT_NOAUTOSPAWN, NULL);
	if (on < 0)
	{
		ft_dprintf(STDERR_FILENO, "Failed to connect PulseAudio server: %s\n",
			pa_strerror(pa_context_errno(env->pa->ctx)));
		return (ret);
	}
	if (pa_threaded_mainloop_start(env->pa->loop) < 0)
	{
		ft_dprintf(STDERR_FILENO, "Mainloop failed\n");
		return (ret);
	}
	run_mainloop(env->pa);
	*ret = 0;
	return (kill_pa(env->pa), ret);
}
