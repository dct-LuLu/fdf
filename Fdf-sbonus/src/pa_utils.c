/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:01:36 by jaubry--          #+#    #+#             */
/*   Updated: 2025/02/11 17:41:21 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "osci.h"

static void	stream_read_callback(pa_stream *s, size_t buf_size, void *userdata)
{
	t_env	*env;

	env = (t_env *)userdata;
	env->buf_len = buf_size / sizeof(int16_t);
	if (pa_stream_peek(s, (const void **)&env->buffer, &buf_size) == 0)
		pa_stream_drop(s);
}

static void	create_pa_structs(pa_sample_spec *sample_spec, pa_buffer_attr *attr)
{
	*sample_spec = (pa_sample_spec)
	{
		.format = PA_SAMPLE_S16LE,
		.rate = SAMPLE_RATE,
		.channels = CHANNELS
	};
	*attr = (pa_buffer_attr)
	{
		.maxlength = UNDEF,
		.minreq = UNDEF,
		.prebuf = UNDEF,
		.fragsize = 1,
		.tlength = BUFFER_DURATION_MS
	};
}

static void	pa_setup_stream(pa_context *c, t_env *env)
{
	t_pa			*pa;
	pa_sample_spec	sample_spec;
	pa_buffer_attr	attr;
	int				ret;

	pa = env->pa;
	create_pa_structs(&sample_spec, &attr);
	pa->stream = pa_stream_new(c, "Audio Capture", &sample_spec, NULL);
	if (!pa->stream)
	{
		ft_dprintf(STDERR_FILENO, "Failed to create stream\n");
		pa_threaded_mainloop_signal(pa->loop, 0);
		return ;
	}
	pa_stream_set_read_callback(pa->stream, stream_read_callback, env);
	ret = pa_stream_connect_record(pa->stream, DEVICE, &attr,
			PA_STREAM_ADJUST_LATENCY);
	if (ret < 0)
	{
		ft_dprintf(STDERR_FILENO, "Failed to connect to monitor source: %s\n",
			pa_strerror(pa_context_errno(c)));
		pa_threaded_mainloop_signal(pa->loop, 0);
		return ;
	}
}

static void	pa_end_ctx(t_pa *pa, pa_context_state_t state)
{
	if (state == PA_CONTEXT_FAILED)
		ft_dprintf(STDERR_FILENO, "PulseAudio context failed\n");
	else
		ft_printf("PulseAudio context terminated.\n");
	pa_threaded_mainloop_signal(pa->loop, 0);
}

void	context_state_callback(pa_context *c, void *userdata)
{
	pa_context_state_t	state;
	t_env				*env;

	env = (t_env *)userdata;
	state = pa_context_get_state(c);
	if (state == PA_CONTEXT_READY)
		pa_setup_stream(c, env);
	else if (state == PA_CONTEXT_FAILED || state == PA_CONTEXT_TERMINATED)
		pa_end_ctx(env->pa, state);
	else if (state == PA_CONTEXT_CONNECTING)
		ft_printf("Context is connecting...\n");
	else if (state == PA_CONTEXT_AUTHORIZING)
		ft_printf("Context is authorizing...\n");
}
