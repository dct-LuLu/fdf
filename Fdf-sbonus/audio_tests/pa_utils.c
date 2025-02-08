/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:42:39 by jaubry--          #+#    #+#             */
/*   Updated: 2025/02/08 01:18:25 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "audio_tests.h"

/*
	Function called each loop.
*/
static void	stream_read_callback(pa_stream *s, size_t buf_size, void *userdata)
{
	int16_t	*data;

	(void)userdata;
	if (pa_stream_peek(s, (const void **)&data, &buf_size) == 0)
	{
		display_audio(data, buf_size / sizeof(int16_t));
		pa_stream_drop(s);
	}
}

/*
	Function to setup the stream and handle failure, for creation of the
	stream or connection to the monitor source.
*/
static void	pa_setup_stream(pa_context *c, t_pa *pa)
{
	int				ret;
	pa_sample_spec	sample_spec;

	sample_spec = (pa_sample_spec)
	{
		.format = PA_SAMPLE_S16LE,
		.rate = SAMPLE_RATE,
		.channels = CHANNELS
	};
	pa->stream = pa_stream_new(c, "Audio Capture", &sample_spec, NULL);
	if (!pa->stream)
	{
		ft_dprintf(STDERR_FILENO, "Failed to create PulseAudio stream\n");
		pa_mainloop_quit(pa->loop, 0);
		return ;
	}
	pa_stream_set_read_callback(pa->stream, stream_read_callback, NULL);
	ret = pa_stream_connect_record(pa->stream, DEVICE, NULL, PA_STREAM_NOFLAGS);
	if (ret < 0)
	{
		ft_dprintf(STDERR_FILENO, "Failed to connect to monitor source:%s\n",
			pa_strerror(pa_context_errno(c)));
		pa_mainloop_quit(pa->loop, 0);
		return ;
	}
}

/*
	Function to handle and quit pa_context fail or termination.
*/
static void	pa_end_ctx(t_pa *pa, pa_context_state_t state)
{
	if (state == PA_CONTEXT_FAILED)
		ft_dprintf(STDERR_FILENO, "PulseAudio context failed\n");
	else
		ft_printf("PulseAudio context terminated.\n");
	pa_mainloop_quit(pa->loop, 0);
	pthread_exit(NULL);
}

/*
	Function that handle PulseAudio context states
*/
void	context_state_callback(pa_context *c, void *userdata)
{
	t_pa				*pa;
	pa_context_state_t	state;

	pa = (t_pa *)userdata;
	state = pa_context_get_state(c);
	if (state == PA_CONTEXT_READY)
		pa_setup_stream(c, pa);
	else if ((state == PA_CONTEXT_FAILED) || (state == PA_CONTEXT_TERMINATED))
		pa_end_ctx(pa, state);
	else if (state == PA_CONTEXT_CONNECTING)
		ft_printf("Context is connecting...\n");
	else if (state == PA_CONTEXT_AUTHORIZING)
		ft_printf("Context is authorizing...\n");
}
