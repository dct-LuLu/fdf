/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   better_alsa_faders.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:42:39 by jaubry--          #+#    #+#             */
/*   Updated: 2025/02/05 18:31:36 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pulse/pulseaudio.h>
#include <pulse/thread-mainloop.h>
#include <math.h>
#include "libft.h"
#include "fdf.h"

#define SAMPLE_RATE 192000
#define CHANNELS 2
#define BUFFER_DURATION_MS 1

static pa_threaded_mainloop		*mainloop = NULL;
static pa_mainloop_api	*mainloop_api = NULL;
static pa_context		*context = NULL;
static pa_stream		*stream = NULL;

pthread_mutex_t			stop_mutex = PTHREAD_MUTEX_INITIALIZER;
volatile sig_atomic_t	stop = 0;
pthread_mutex_t			audio_mutex = PTHREAD_MUTEX_INITIALIZER;
int16_t					*buffer	= NULL;
size_t					buf_len = 0;

void	pa_quit(void);

void	handle_signal(int signal)
{
	(void)signal;
	pthread_mutex_lock(&stop_mutex);
	stop = 1;
	pthread_mutex_unlock(&stop_mutex);
}

void stream_read_callback(pa_stream *s, size_t buf_size, void *userdata)
{
    (void)userdata;  // Suppress unused parameter warning

    buf_len = buf_size / sizeof(int16_t);
    if (pa_stream_peek(s, (const void **)&buffer, &buf_size) == 0)
        pa_stream_drop(s);
}

void context_state_callback(pa_context *c, void *userdata)
{
    (void)userdata;  // Suppress unused parameter warning
    pa_context_state_t state = pa_context_get_state(c);

    if (state == PA_CONTEXT_READY)
    {
        pa_sample_spec sample_spec = {
            .format = PA_SAMPLE_S16LE,
            .rate = SAMPLE_RATE,
            .channels = CHANNELS
        };

        pa_buffer_attr  attr = {
            .maxlength = (uint32_t)-1,
            .minreq = (uint32_t)-1,
            .prebuf = (uint32_t)-1,
            .fragsize = 1,
            .tlength = 1
        };//allow fast signal lol, doesnt work on ubuntu tho, but izokay it gives already the fastest
        const char *monitor_source_name = "alsa_output.usb-GuangZhou_FiiO_Electronics_Co._Ltd_FiiO_K7-00.analog-stereo.monitor";

        // Create and configure the stream for recording from the monitor source
        stream = pa_stream_new(c, "Audio Capture", &sample_spec, NULL);
        if (!stream)
        {
            fprintf(stderr, "Failed to create stream\n");
            pa_threaded_mainloop_signal(mainloop, 0);
            return;
        }

        // Set the read callback for the stream
        pa_stream_set_read_callback(stream, stream_read_callback, NULL);

        // Connect the stream to the specific monitor source
        if (pa_stream_connect_record(stream, monitor_source_name, &attr, PA_STREAM_ADJUST_LATENCY) < 0)
        {
            fprintf(stderr, "Failed to connect to monitor source: %s\n", pa_strerror(pa_context_errno(c)));
            pa_threaded_mainloop_signal(mainloop, 0);
            return;
        }
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

    // Initialize the PulseAudio mainloop and context
    mainloop = pa_threaded_mainloop_new();
    if (!mainloop)
    {
    	fprintf(stderr, "Failed to create pulseaudio mainloop\n");
    	*ret = 1;
    	return ((void *)ret);
    }

    mainloop_api = pa_threaded_mainloop_get_api(mainloop);
    context = pa_context_new(mainloop_api, "PulseAudio Recording Example");

    if (!context)
    {
        fprintf(stderr, "Failed to create PulseAudio context\n");
        *ret = 1;
        return ((void*)ret);
    }

    // Set the context state callback
    pa_context_set_state_callback(context, context_state_callback, NULL);

    // Connect to the PulseAudio server
    if (pa_context_connect(context, NULL, PA_CONTEXT_NOAUTOSPAWN, NULL) < 0)
    {
        fprintf(stderr, "Failed to connect to PulseAudio server: %s\n", pa_strerror(pa_context_errno(context)));
        *ret = 1;
        return ((void*)ret);
    }

	if (pa_threaded_mainloop_start(mainloop) < 0)
	{
		fprintf(stderr, "Aled\n");
		*ret = 1;
		return ((void*)ret);
	}

    // Run the mainloop
    
    bool	in = true;
    while (in)
    {
    	pa_threaded_mainloop_lock(mainloop);
    	pa_threaded_mainloop_wait(mainloop);
    	pthread_mutex_lock(&stop_mutex);
    	if (stop)
    	{
    		fprintf(stderr, "quiting audio loop\n");
    		in = false;
    	}
    	pthread_mutex_unlock(&stop_mutex);
    	pa_threaded_mainloop_unlock(mainloop);
    }

	pa_quit();
	*ret = 0;
    return ((void *)ret);
}

void	pa_quit(void)
{
	ft_printf("Exiting program...\n");
	pa_stream_unref(stream);
	pa_context_unref(context);
	pa_threaded_mainloop_stop(mainloop);
	pa_threaded_mainloop_free(mainloop);
}

int	th_mlx__th_pa(void)
{
    //pthread_t	th_audio;
	pthread_t	th_mlx;
    int			*ret_audio;
    int			*ret_mlx;

    ret_mlx = malloc(sizeof(int));
    ret_audio = malloc(sizeof(int));
	signal(SIGINT, handle_signal);

    //if (pthread_create(&th_audio, NULL, &snd, ret_audio) != 0)
    //	exit(1);
    //snd(ret_audio);
    pthread_create(&th_mlx, NULL, &mlx_thread_feur, ret_mlx);
	snd(ret_audio);
    //pthread_join(th_audio, (void **)&ret_audio);
    if (pthread_join(th_mlx, (void **)&ret_mlx) != 0)
		return (printf("aled\n\n"), 1);
	//pthread_join(th_audio, (void **)&ret_audio);

    free(ret_audio);
    free(ret_mlx);
	return (ret_mlx || ret_audio);
}

int main(void)
{
	th_mlx__th_pa();
    return (0);
}

/*
    Mainloop Integration:
        The PulseAudio mainloop (pa_mainloop) and context (pa_context) are set up to run the audio capture in the background.
        The context_state_callback function initializes the audio capture when the context is ready.

    Audio Processing:
        The stream_read_callback function processes the audio in chunks, calculates the RMS and peak dB levels for both left and right channels, and displays the corresponding values using display_dBfs_gauge.

    Error Handling:
        Error handling has been improved with appropriate checks for context state changes (e.g., failed or terminated state).

    Using PulseAudio Streaming:
        The audio data is captured from the specified monitor source ("alsa_output.usb-GuangZhou_FiiO_Electronics_Co._Ltd_FiiO_K7-00.analog-stereo.monitor").
        The audio is processed within the callback, and the mainloop ensures continuous data capture.
*/
