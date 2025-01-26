/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   broken-delay-dB-jauge.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:46:35 by jaubry--          #+#    #+#             */
/*   Updated: 2025/01/26 02:13:20 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>
#include <pulse/simple.h>
#include <pulse/error.h>
#include <math.h>

#define SAMPLE_RATE 48000
#define CHANNELS 2
#define BUFFER_DURATION_MS 5

#define GAUGE_WIDTH 40  // The width of the gauge (number of characters)
#define MIN_DB -60     // Minimum dBFS (for silence, or the lowest visible level)
#define MAX_DB 0       // Maximum dBFS (representing 0 dBFS, the maximum level)

/*
	Function that computes the RMS of the PCM signal.
	Takes in parameter the PCM signal, it's lenght, and the targeted channel
*/
double	compute_rms(int16_t *buffer, size_t buf_len, int channel_i)
{
    size_t  i;
    double  rms;
    double  normalized_sample;

    i = 0;
    rms = 0.0;
    while ((i + channel_i) < buf_len)
    {
        normalized_sample = buffer[i + channel_i] / 32768.0;
        rms += normalized_sample * normalized_sample;
        i += CHANNELS;
    }
    return (sqrt(rms / (buf_len / CHANNELS)));
}

double  convert_dbfs(double rms)
{
    return (20 * log10(rms));
}

double  peak_db(int16_t *buffer, size_t buf_len, int channel_i)
{
    size_t  i;
    int peak;
    int abs_sample;

    i = 0;
    peak = 0;
    while ((i + channel_i) < buf_len)
    {
        abs_sample = abs(buffer[i + channel_i]);
        if (abs_sample > peak)
            peak = abs_sample;
        i += CHANNELS;
    }
    return (20 * log10((double)peak / 32768.0));
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

    // Display the gauge
    printf("[");
    for (int i = 0; i < GAUGE_WIDTH; i++)
    {
        if (i < num_bars)
            printf("#");  // Active bar
        else
            printf(" ");  // Empty space
    }
    printf("] %.2f dBFS\n", peak_dbfs);
}
//double  compute_

void *audio_processing_thread() {
    // Set real-time scheduling for this thread
   /* 
    struct sched_param param;
    param.sched_priority = sched_get_priority_max(SCHED_FIFO);
    if (pthread_setschedparam(pthread_self(), SCHED_FIFO, &param) != 0) {
        perror("Failed to set real-time scheduling");
        return NULL;
    }
    */

    static const pa_sample_spec ss = {
        .format = PA_SAMPLE_S16LE, //Signed 16 integer bit PCM, little endian. -32768 to 32767
        .rate = SAMPLE_RATE,
        .channels = CHANNELS
    };

    pa_simple *s = NULL;
    int error;

    if (!(s = pa_simple_new(NULL, "AudioMonitor", PA_STREAM_RECORD, "alsa_output.usb-GuangZhou_FiiO_Electronics_Co._Ltd_FiiO_K7-00.analog-stereo.monitor", "record", &ss, NULL, NULL, &error))) {
        fprintf(stderr, "pa_simple_new() failed: %s\n", pa_strerror(error));
        return NULL;
    }

    // Calculate buffer size
    size_t buf_len = (SAMPLE_RATE * CHANNELS * BUFFER_DURATION_MS / 1000);
    size_t buf_size = buf_len * sizeof(int16_t);
    int16_t *buffer = malloc(buf_size);

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
        //double rms = compute_rms(buffer, buf_len, 0);
       // double db = 20 * log10(rms);

        // Calculate gauge level
        /*int gauge_level = (int)((db + 60) / 60 * GAUGE_WIDTH); // Normalize dB to gauge width
        if (gauge_level < 0) gauge_level = 0;
        if (gauge_level > GAUGE_WIDTH) gauge_level = GAUGE_WIDTH;
*/
        double l_rms = compute_rms(buffer, buf_len, 0);
        double r_rms = compute_rms(buffer, buf_len, 1);
        double l_peak = peak_db(buffer, buf_len, 0);
        double r_peak = peak_db(buffer, buf_len, 1);
        // Print dB and gauge
        printf("FL: %.2fRMS\t%.2fdBFS\n", l_rms, convert_dbfs(l_rms));
        display_dBfs_gauge(l_peak);

        printf("\n\n");
        printf("FR: %.2fRMS\t%.2fdBFS\n", r_rms, convert_dbfs(r_rms));
        display_dBfs_gauge(r_peak);
        printf("\n\n\n\nPCM SIGNAL:\n");


        for (size_t i = 0; i < buf_len; i++) {
        	printf("%d\t", buffer[i]);
        }
        /*printf("[");
        for (int i = 0; i < GAUGE_WIDTH; i++) {
            if (i < gauge_level) {
                printf("#");
            } else {
                printf(" ");
            }
        }
        printf("]\n");*/
        //break;
    }

    free(buffer);
    pa_simple_free(s);

    return NULL;
}

int main() {
    audio_processing_thread();
    /*
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
    */

    return EXIT_SUCCESS;
}

