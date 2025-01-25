/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   broken-delay-dB-jauge.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:46:35 by jaubry--          #+#    #+#             */
/*   Updated: 2025/01/24 12:06:34 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>
#include <pulse/simple.h>
#include <pulse/error.h>
#include <math.h>

#define SAMPLE_RATE 48000
#define CHANNELS 2
#define BUFFER_DURATION_MS 1
#define GAUGE_WIDTH 50 // Width of the gauge in characters

void *audio_processing_thread(void *arg) {
    (void)arg; // Mark the parameter as unused

    // Set real-time scheduling for this thread
   /* 
    struct sched_param param;
    param.sched_priority = sched_get_priority_max(SCHED_FIFO);
    if (pthread_setschedparam(pthread_self(), SCHED_FIFO, &param) != 0) {
        perror("Failed to set real-time scheduling");
        return NULL;
    }
    */


    // PulseAudio sample specification
    static const pa_sample_spec ss = {
        .format = PA_SAMPLE_S16LE,
        .rate = SAMPLE_RATE,
        .channels = CHANNELS
    };

    pa_simple *s = NULL;
    int error;

    // Connect to the desired monitor source
    if (!(s = pa_simple_new(NULL, "AudioMonitor", PA_STREAM_RECORD, "alsa_output.usb-GuangZhou_FiiO_Electronics_Co._Ltd_FiiO_K7-00.analog-stereo.monitor", "record", &ss, NULL, NULL, &error))) {
        fprintf(stderr, "pa_simple_new() failed: %s\n", pa_strerror(error));
        return NULL;
    }

    // Calculate buffer size
    size_t buf_size = (SAMPLE_RATE * CHANNELS * BUFFER_DURATION_MS / 1000) * sizeof(int16_t);
    int16_t *buffer = (int16_t *)malloc(buf_size);

    // Capture loop
    while (1) {
        // Clear the terminal screen
        printf("\033[H\033[J");

        // Read audio data
        if (pa_simple_read(s, buffer, buf_size, &error) < 0) {
            fprintf(stderr, "pa_simple_read() failed: %s\n", pa_strerror(error));
            break;
        }

        // Calculate RMS and convert to dB
        double rms = 0.0;
        for (size_t i = 0; i < buf_size / sizeof(int16_t); i++) {
            rms += buffer[i] * buffer[i];
        }
        rms = sqrt(rms / (buf_size / sizeof(int16_t)));
        double db = 20 * log10(rms);

        // Calculate gauge level
        int gauge_level = (int)((db + 60) / 60 * GAUGE_WIDTH); // Normalize dB to gauge width
        if (gauge_level < 0) gauge_level = 0;
        if (gauge_level > GAUGE_WIDTH) gauge_level = GAUGE_WIDTH;

        // Print dB and gauge
        printf("dB: %.2f\n", db);
        printf("[");
        for (int i = 0; i < GAUGE_WIDTH; i++) {
            if (i < gauge_level) {
                printf("#");
            } else {
                printf(" ");
            }
        }
        printf("]\n");
    }

    free(buffer);
    pa_simple_free(s);

    return NULL;
}

int main() {
    pthread_t thread;
    int result;

    // Create the audio processing thread
    result = pthread_create(&thread, NULL, audio_processing_thread, NULL);
    if (result != 0) {
        fprintf(stderr, "Error creating thread: %d\n", result);
        return EXIT_FAILURE;
    }

    // Wait for the thread to finish (in a real application, you might not do this)
    pthread_join(thread, NULL);

    return EXIT_SUCCESS;
}

