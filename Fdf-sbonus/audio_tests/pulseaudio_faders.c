/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pulseaudio_faders.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:42:39 by jaubry--          #+#    #+#             */
/*   Updated: 2025/02/06 21:09:21 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pulse/pulseaudio.h>
#include <math.h>
#include <signal.h>
#include <pthread.h>
#include "libft.h"
#include "audio_tests.h"

/*
	static pa_mainloop		*mainloop = NULL;
	static pa_mainloop_api	*mainloop_api = NULL;
	static pa_context		*context = NULL;
	static pa_stream		*stream = NULL;
*/

volatile sig_atomic_t	stop = 0;

void	handle_signal(int signal)
{
	(void)signal;
	stop = 1;
}

double compute_rms(int16_t *buffer, size_t buf_len, int channel_i)
{
    size_t i;
    double rms = 0.0;
    double normalized_sample;

    for (i = 0; i < buf_len; i += CHANNELS)
    {
        normalized_sample = buffer[i + channel_i] / MAX_SAMPLE;
        rms += normalized_sample * normalized_sample;
    }
    return sqrt(rms / (buf_len / CHANNELS));
}

double convert_dbfs(double rms)
{
    return (20 * log10(rms));
}

double peak_db(int16_t *buffer, size_t buf_len, int channel_i)
{
    size_t i;
    int peak = 0;
    int abs_sample;

    for (i = 0; i < buf_len; i += CHANNELS)
    {
        abs_sample = abs(buffer[i + channel_i]);
        if (abs_sample > peak)
            peak = abs_sample;
    }
    return (20 * log10((double)peak / MAX_SAMPLE));
}

void display_dBfs_gauge(double peak_dbfs)
{
    // Clamp the peak dBFS value to be between MIN_DB and MAX_DB
    if (peak_dbfs > MAX_DB)
        peak_dbfs = MAX_DB;

    // Map the peak dBFS to a position on the gauge
    double range = MAX_DB - MIN_DB;        // The total range in dB (from -60 dB to 0 dB)
    double scale = (peak_dbfs - MIN_DB) / range;  // Scale factor to convert dB to percentage

    // Calculate the number of "bars" (segments) for the gauge
    int num_bars = (int)(scale * GAUGE_WIDTH);  // The number of characters to represent the level

    printf("[");
    for (int i = 0; i < GAUGE_WIDTH; i++)
    {
        if (i < num_bars)
            printf("#");
        else
            printf(" ");
    }
    printf("] %.2f peak dBFS\n", peak_dbfs);
}

void stream_read_callback(pa_stream *s, size_t buf_size, void *userdata)
{
    (void)userdata;

    int16_t *data;
    size_t buf_len = buf_size / sizeof(int16_t);
    if (pa_stream_peek(s, (const void **)&data, &buf_size) == 0)
    {
        // Process the audio data here
        double l_rms = compute_rms(data, buf_len, 0);
        double r_rms = compute_rms(data, buf_len, 1);
        double l_peak = peak_db(data, buf_len, 0);
        double r_peak = peak_db(data, buf_len, 1);

		printf("\033[H\033[J");
        // Print dB and gauge
        printf("FL: %.2fRMS\t%.2fdBFS\n", l_rms, convert_dbfs(l_rms));
        display_dBfs_gauge(l_peak);

        printf("\n\n");
        printf("FR: %.2fRMS\t%.2fdBFS\n", r_rms, convert_dbfs(r_rms));
        display_dBfs_gauge(r_peak);

		printf("\n\nPCM SIGNAL: %zu\n", buf_len);


        for (size_t i = 0; i < buf_len; i++) {
        	printf("%d\t", data[i]);
            if ((i + 1) % 24 == 0)
                printf("\n");
        }
        printf("\n");
        // After processing, forget the data to continue receiving more
        pa_stream_drop(s);
    }
}

void context_state_callback(pa_context *c, void *userdata)
{
	t_pa *pa;
    pa = (t_pa*)userdata;  // Suppress unused parameter warning

    pa_context_state_t state = pa_context_get_state(c);

    if (state == PA_CONTEXT_READY)
    {
        pa_sample_spec sample_spec = {
            .format = PA_SAMPLE_S16LE,
            .rate = SAMPLE_RATE,
            .channels = CHANNELS
        };
        const char *monitor_source_name = DEVICE;

        // Create and configure the pa.stream for recording from the monitor source
        pa->stream = pa_stream_new(c, "Audio Capture", &sample_spec, NULL);
        if (!pa->stream)
        {
            ft_dprintf(STDERR_FILENO, "Failed to create pa.stream\n");
            pa_mainloop_quit(pa->loop, 0);
            return;
        }

        // Set the read callback for the pa.stream
        pa_stream_set_read_callback(pa->stream, stream_read_callback, NULL);

        // Connect the pa.stream to the specific monitor source
        if (pa_stream_connect_record(pa->stream, monitor_source_name, NULL, PA_STREAM_NOFLAGS) < 0)
        {
            ft_dprintf(STDERR_FILENO, "Failed to connect to monitor source: %s\n", pa_strerror(pa_context_errno(c)));
            pa_mainloop_quit(pa->loop, 0);
            return;
        }
    }
    else if (state == PA_CONTEXT_FAILED || state == PA_CONTEXT_TERMINATED)
    {
        ft_dprintf(STDERR_FILENO, "PulseAudio context failed or terminated.\n");
        pa_mainloop_quit(pa->loop, 0);
        exit(0);
    }
    else if (state == PA_CONTEXT_CONNECTING)
        printf("Context is connecting...\n");
    else if (state == PA_CONTEXT_AUTHORIZING)
        printf("Context is authorizing...\n");
}

void	*snd(void *args)
{
	t_pa	*pa;
	(void)args;
	int	*ret;

	pa = NULL;
	ret = malloc(sizeof(int));
    pa->loop = pa_mainloop_new();
    pa->api = pa_mainloop_get_api(pa->loop);
    pa->ctx = pa_context_new(pa->api, "PulseAudio Recording Example");

    if (!pa->ctx)
    {
        ft_dprintf(STDERR_FILENO, "Failed to create PulseAudio context\n");
        *ret = 1;
        return ((void*)ret);
    }

    // Set the pa.ctx state callback
    pa_context_set_state_callback(pa->ctx, context_state_callback, NULL);

    // Connect to the PulseAudio server
    if (pa_context_connect(pa->ctx, NULL, PA_CONTEXT_NOAUTOSPAWN, NULL) < 0)
    {
        ft_dprintf(STDERR_FILENO, "Failed to connect to PulseAudio server: %s\n", pa_strerror(pa_context_errno(pa->ctx)));
        *ret = 1;
        return ((void*)ret);
    }

    while (!stop)
    {
    	int err = pa_mainloop_iterate(pa->loop, 0, NULL);
    	if (err < 0)
    	{
        	ft_dprintf(STDERR_FILENO, "Mainloop failed\n");
        	break;
    	}
    }

    printf("Exiting program...\n");
    pa_stream_unref(pa->stream);
    pa_context_unref(pa->ctx);
    pa_mainloop_free(pa->loop);

	*ret = 0;
    return ((void*)ret);
}

int	main(void)
{
	pthread_t	th_audio;
	int			*ret;

	signal(SIGINT, handle_signal);
	pthread_create(&th_audio, NULL, &snd, NULL);
	pthread_join(th_audio, (void **)&ret);
	printf("thread returned: %d\n", *ret);
	free(ret);
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
