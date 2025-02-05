/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   better_alsa_faders.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:42:39 by jaubry--          #+#    #+#             */
/*   Updated: 2025/02/05 12:52:58 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pulse/pulseaudio.h>
#include <math.h>
#include "libft.h"
#include "fdf.h"

#define SAMPLE_RATE 192000
#define CHANNELS 2
#define BUFFER_DURATION_MS 1
#define GAUGE_WIDTH 120  // The width of the gauge (number of characters)
#define MIN_DB -60     // Minimum dBFS (for silence, or the lowest visible level)
#define MAX_DB 0       // Maximum dBFS (representing 0 dBFS, the maximum level)

static pa_mainloop *mainloop = NULL;
static pa_mainloop_api *mainloop_api = NULL;
static pa_context *context = NULL;
static pa_stream *stream = NULL;

pthread_mutex_t	stop_mutex = PTHREAD_MUTEX_INITIALIZER;
volatile sig_atomic_t	stop = 0;
pthread_mutex_t	audio_mutex = PTHREAD_MUTEX_INITIALIZER;
int16_t	*buffer	= NULL;
size_t  buf_len = 0;

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
            pa_mainloop_quit(mainloop, 0);
            return;
        }

        // Set the read callback for the stream
        pa_stream_set_read_callback(stream, stream_read_callback, NULL);

        // Connect the stream to the specific monitor source
        if (pa_stream_connect_record(stream, monitor_source_name, &attr, PA_STREAM_ADJUST_LATENCY) < 0)
        {
            fprintf(stderr, "Failed to connect to monitor source: %s\n", pa_strerror(pa_context_errno(c)));
            pa_mainloop_quit(mainloop, 0);
            return;
        }
    }
    else if (state == PA_CONTEXT_FAILED || state == PA_CONTEXT_TERMINATED)
    {
        fprintf(stderr, "PulseAudio context failed or terminated.\n");
        pa_mainloop_quit(mainloop, 0);
        exit(0);
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
    mainloop = pa_mainloop_new();
    mainloop_api = pa_mainloop_get_api(mainloop);
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
    // Run the mainloop
    bool	in = true;
    while (in)
    {
    	int err = pa_mainloop_iterate(mainloop, 0, NULL);
    	pthread_mutex_lock(&stop_mutex);
    	if (stop)
    	{
    		fprintf(stderr, "quiting audio loop\n");
    		in = false;
    	}
    	pthread_mutex_unlock(&stop_mutex);
    	if (err < 0)
    	{
        	fprintf(stderr, "Mainloop failed\n");
        	break;
    	}
    }

    // Clean up
    printf("Exiting program...\n");
    pa_stream_unref(stream);
    pa_context_unref(context);
    pa_mainloop_free(mainloop);

	*ret = 0;
    return ((void *)ret);
}

// ################################## SOLO NO THREADS ##################################
int	mlx_only(void) // only MLX
{
    int			*ret_mlx;

    ret_mlx = malloc(sizeof(int));
	signal(SIGINT, handle_signal);;
    
	mlx_thread_feur(ret_mlx);

    free(ret_mlx);
	return (0);
}

int	pa_only(void) // only PULSEAUDIO
{
    int			*ret_audio;

    ret_audio = malloc(sizeof(int));
	signal(SIGINT, handle_signal);

    snd(ret_audio);

    free(ret_audio);
	return (0);
}

// ################################## SOLO THREADED ##################################
int	th_pa_only(void) // only PULSEAUDIO THREADED
{
    pthread_t	th_audio;
    int			*ret_audio;

    ret_audio = malloc(sizeof(int));
	signal(SIGINT, handle_signal);

    pthread_create(&th_audio, NULL, &snd, ret_audio);

    pthread_join(th_audio, (void **)&ret_audio);

    free(ret_audio);
	return (0);
}

int	th_mlx_only(void) // only MLX THREADED
{
	pthread_t	th_mlx;
    int			*ret_mlx;

    ret_mlx = malloc(sizeof(int));
	signal(SIGINT, handle_signal);

	pthread_create(&th_mlx, NULL, &mlx_thread_feur, ret_mlx);

	pthread_join(th_mlx, (void **)&ret_mlx);

    free(ret_mlx);
	return (0);
}

// ############################ THREADED AND NON-THREADED #######################
int	mlx__th_pa(void) // MLX + PULSEAUDIO THREADED
{
    pthread_t	th_audio;
    int			*ret_audio;
    int			*ret_mlx;

    ret_mlx = malloc(sizeof(int));
    ret_audio = malloc(sizeof(int));
	signal(SIGINT, handle_signal);

    pthread_create(&th_audio, NULL, &snd, ret_audio);
	mlx_thread_feur(ret_mlx);
    pthread_join(th_audio, (void **)&ret_audio);

    free(ret_audio);
    free(ret_mlx);
	return (0);
}

int	th_mlx__pa(void) // MLX THREADED + PULSEAUDIO
{
	pthread_t	th_mlx;
    int			*ret_audio;
    int			*ret_mlx;

    ret_mlx = malloc(sizeof(int));
    ret_audio = malloc(sizeof(int));
	signal(SIGINT, handle_signal);

	pthread_create(&th_mlx, NULL, &mlx_thread_feur, ret_mlx);

    snd(ret_audio);

	pthread_join(th_mlx, (void **)&ret_mlx);

    free(ret_audio);
    free(ret_mlx);
	return (0);
}



// ################################## FULL THREADED ##################################
int	th_mlx__th_pa(void) // MLX THREADED + PULSEAUDIO THREADED
{
    pthread_t	th_audio;
	pthread_t	th_mlx;
    int			*ret_audio;
    int			*ret_mlx;

    ret_mlx = malloc(sizeof(int));
    ret_audio = malloc(sizeof(int));
	signal(SIGINT, handle_signal);

    pthread_create(&th_audio, NULL, &snd, ret_audio);
	pthread_create(&th_mlx, NULL, &mlx_thread_feur, ret_mlx);

    pthread_join(th_audio, (void **)&ret_audio);
	pthread_join(th_mlx, (void **)&ret_mlx);

    free(ret_audio);
    free(ret_mlx);
	return (ret_mlx || ret_audio);
}

// ################################## FULL NOT THREADED ##################################
int	mlx__pa(void) // MLX THREADED + PULSEAUDIO THREADED
{
    int			*ret_audio;
    int			*ret_mlx;

    ret_mlx = malloc(sizeof(int));
    ret_audio = malloc(sizeof(int));
	signal(SIGINT, handle_signal);
    	
    mlx_thread_feur(ret_mlx);
    snd(ret_audio);

    free(ret_audio);
    free(ret_mlx);
	return (0);
}

void    *test(void *arg)
{
    bool    in;

    in = true;
    while (in)
    {
        pthread_mutex_lock(&stop_mutex);
        if (stop)
            in = false;
        pthread_mutex_unlock(&stop_mutex);
        sleep(5);
    }
    return (arg);
}

int mlx__th_else(void)
{
    pthread_t	th_else;
    int			*ret_else;
    t_env	*env;
    //int			*ret_mlx;
    env = calloc(1, sizeof(t_env));
	if (!env)
		return (1);

	env->mlx = mlx_init();
	if (!env->mlx)
	{
		free(env);
		return (1);
	}
	env->win = NULL;
	env->win = mlx_new_window(env->mlx, WIDTH, HEIGHT, "osci");
	if (!env->win)
	{
		ft_dprintf(STDERR_FILENO, "aled\n");
		kill_mlx(env);
		return (1);
	}
	env->img.img = NULL;
	env->img.addr = NULL;
    //ret_mlx = malloc(sizeof(int));
    ret_else = malloc(sizeof(int));
    //*ret_mlx = 0;
    *ret_else = 0;
	signal(SIGINT, handle_signal);

    pthread_create(&th_else, NULL, &test, ret_else);
	mlx_thread_feur(env);
    pthread_join(th_else, (void **)&ret_else);


    free(ret_else);
    //free(ret_mlx);
	return (0);
}


int main(void)
{
    
    //mlx_only();//      MLX                                              #7fff00
    //th_mlx_only();//   MLX THREADED                                     #ff0000 


    //pa_only();//                               PULSEAUDIO               #7fff00
    //th_pa_only();//                            PULSEAUDIO THREADED      #7fff00


    //mlx__th_pa();//    MLX                     PULSEAUDIO THREADED      #ff0000
    //th_mlx__pa();//    MLX THREADED            PULSEAUDIO               #ff0000


	th_mlx__th_pa();// MLX THREADED            PULSEAUDIO THREADED      #ff0000  

    //mlx__pa();//       MLX                     PULSEAUDIO               #ff0000
	//mlx__th_else();//  MLX                     NOTHING    THREADED      #ff0000
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
