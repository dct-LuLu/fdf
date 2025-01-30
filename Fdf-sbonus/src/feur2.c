/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feur2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:42:38 by jaubry--          #+#    #+#             */
/*   Updated: 2025/01/29 15:34:21 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <pulse/pulseaudio.h>
#include <mlx.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

int handle_key(int keycode, void *param)
{
	(void *)param;
    if (keycode == 65307)  // Keycode 53 is Esc in most configurations
        exit(0);  // Exit immediately after flag change
    return (0);
}

// PulseAudio handling function (audio thread)
void *audio_thread_function(void *arg) {
    (void)arg;
    // Set up PulseAudio, handle events, etc.
    pa_threaded_mainloop *pa_mainloop;

    pa_mainloop = pa_threaded_mainloop_new();

    // Initialize PulseAudio context, stream, etc.
    // Run PulseAudio's main loop in this thread
    pa_threaded_mainloop_start(pa_mainloop);
    
    // Cleanup and exit
    pa_threaded_mainloop_free(pa_mainloop);
    return NULL;
}

int main()
{
    void *mlx_ptr = mlx_init();
    if (!mlx_ptr)
    {
        fprintf(stderr, "Error initializing MLX\n");
        return 1;
    }

    // Create a new window using MLX
    void *win_ptr = mlx_new_window(mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Press ESC to Close");
    if (!win_ptr)
    {
        fprintf(stderr, "Error creating window\n");
        return 1;
    }

    mlx_key_hook(win_ptr, handle_key, NULL);

    // Create and start the audio thread (this thread would handle audio)
    pthread_t audio_thread;
    if (pthread_create(&audio_thread, NULL, audio_thread_function, NULL) != 0)
    {
        fprintf(stderr, "Error creating audio thread\n");
        return 1;
    }

    mlx_loop(mlx_ptr);

    // Wait for the audio thread to finish before exiting
    pthread_join(audio_thread, NULL);

    return 0;
}

