/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   better_alsa_faders.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:42:39 by jaubry--          #+#    #+#             */
/*   Updated: 2025/02/10 21:42:22 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pulse/pulseaudio.h>
#include <pulse/thread-mainloop.h>
#include <math.h>
#include "libft.h"
#include "audio.h"

static pa_threaded_mainloop		*mainloop = NULL;
static pa_mainloop_api	*mainloop_api = NULL;
static pa_context		*context = NULL;
static pa_stream		*stream = NULL;

pthread_mutex_t			audio_mutex = PTHREAD_MUTEX_INITIALIZER;
int16_t					*buffer	= NULL;

size_t					buf_len = 0;

void	pa_quit(void);

void stream_read_callback(pa_stream *s, size_t buf_size, void *userdata)
{
    t_pa    *pa;

    pa = (t_pa*)userdata;
    pa->buf_len = buf_size / sizeof(int16_t);
    if (pa_stream_peek(s, (const void **)&pa->buffer, &buf_size) == 0)
        pa_stream_drop(s);
}

void    pa_setup_stream()
{
        pa_sample_spec sample_spec = {
            .format = PA_SAMPLE_S16LE,
            .rate = SAMPLE_RATE,
            .channels = CHANNELS
        };

        pa_buffer_attr  attr = {
            .maxlength = UNREF,
            .minreq = UNREF,
            .prebuf = UNREF,
            .fragsize = 1,
            .tlength = BUFFER_DURATION_MS
        };

        stream = pa_stream_new(c, "Audio Capture", &sample_spec, NULL);
        if (!stream)
        {
            fprintf(stderr, "Failed to create stream\n");
            pa_threaded_mainloop_signal(mainloop, 0);
            return;
        }

        pa_stream_set_read_callback(stream, stream_read_callback, NULL);

        if (pa_stream_connect_record(stream, monitor_source_name, &attr, PA_STREAM_ADJUST_LATENCY) < 0)
        {
            fprintf(stderr, "Failed to connect to monitor source: %s\n", pa_strerror(pa_context_errno(c)));
            pa_threaded_mainloop_signal(mainloop, 0);
            return;
        }
}

void context_state_callback(pa_context *c, void *userdata)
{
    pa_context_state_t  state;
    t_pa    *pa;

    pa = (t_pa*)userdata;
    state = pa_context_get_state(c);
    if (state == PA_CONTEXT_READY)
    {
    }
    else if (state == PA_CONTEXT_FAILED || state == PA_CONTEXT_TERMINATED)
    {
        fprintf(stderr, "PulseAudio context failed or terminated.\n");
        pa_threaded_mainloop_signal(mainloop, 0);
        return;
    }
    else if (state == PA_CONTEXT_CONNECTING)
        printf("Context is connecting...\n");
    else if (state == PA_CONTEXT_AUTHORIZING)
        printf("Context is authorizing...\n");
}

void	*snd(void *args)
{
    int *ret;
    ret = (int *)args;

	*ret = 1;
    mainloop = pa_threaded_mainloop_new();
    if (!mainloop)
    {
    	ft_dprintf(STDERR_FILENO, "Failed to create pulseaudio mainloop\n");
    	return ((void *)ret);
    }

    mainloop_api = pa_threaded_mainloop_get_api(mainloop);
    context = pa_context_new(mainloop_api, "PulseAudio Recording Example");

    if (!context)
    {
        ft_dprintf(STDERR_FILENO, "Failed to create PulseAudio context\n");
        return ((void*)ret);
    }

    pa_context_set_state_callback(context, context_state_callback, NULL);
    if (pa_context_connect(context, NULL, PA_CONTEXT_NOAUTOSPAWN, NULL) < 0)
    {
        ft_dprintf(STDERR_FILENO, "Failed to connect to PulseAudio server: %s\n", pa_strerror(pa_context_errno(context)));
        return ((void*)ret);
    }

	if (pa_threaded_mainloop_start(mainloop) < 0)
	{
		ft_dprintf(STDERR_FILENO, "Mainloop failed\n");
		return ((void*)ret);
	}

    bool	in = true;
    while (in)
    {
    	pa_threaded_mainloop_lock(mainloop);
    	pa_threaded_mainloop_wait(mainloop);
    	pthread_mutex_lock(&stop_mutex);
    	if (stop)
    	{
    		ft_dprintf(STDERR_FILENO, "quiting audio loop\n");
    		in = false;
    	}
    	pthread_mutex_unlock(&stop_mutex);
    	pa_threaded_mainloop_unlock(mainloop);
    }

	pa_quit();
	*ret = 0;
    return ((void *)ret);
}

/*
	Function that safely close PulseAudio instance.
*/
void	pa_quit(void)
{
	ft_printf("Exiting program...\n");
	pa_stream_unref(stream);
	pa_context_unref(context);
	pa_threaded_mainloop_stop(mainloop);
	pa_threaded_mainloop_free(mainloop);
}

/*
	Function that creates the audio and mlx thread and checks for any errors.
*/
int	main(void)
{
	pthread_t	th_audio;
	pthread_t	th_mlx;
	int			*ret_audio;
	int			*ret_mlx;
	int			error;

    ret_mlx = malloc(sizeof(int));
    if (!ret_mlx)
    	return (1);
    ret_audio = malloc(sizeof(int));
    if (!ret_audio)
		return (free(ret_mlx), 1);
	signal(SIGINT, handle_signal);
    if (pthread_create(&th_audio, NULL, &snd, ret_audio) != 0)
    	return (free(ret_audio), free(ret_mlx), 1);
    if (pthread_create(&th_mlx, NULL, &mlx_thread, ret_mlx) != 0)
    	return (free(ret_audio), free(ret_mlx), 1);
    if (pthread_join(th_mlx, (void **)&ret_mlx) != 0)
		return (free(ret_audio), free(ret_mlx), 1);
	if (pthread_join(th_audio, (void **)&ret_audio) != 0)
		return (free(ret_audio), free(ret_mlx), 1);
	error = (int)(ret_mlx || ret_audio);
	return (free(ret_audio), free(ret_mlx), error);
}
