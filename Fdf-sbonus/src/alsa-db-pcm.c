/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alsa-db-pcm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:07:13 by jaubry--          #+#    #+#             */
/*   Updated: 2025/01/24 15:21:07 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <alsa/asoundlib.h>
#include <math.h>

#define PCM_DEVICE "hw:Loopback,0,1"//"hw:CARD=K7,DEV=0"
#define BUFFER_SIZE 1024

int main() {
    snd_pcm_t *pcm_handle;
    snd_pcm_hw_params_t *params;
    unsigned int rate = 44100;
    int channels = 2;
    int pcm;
    short buffer[BUFFER_SIZE];

    // Open PCM device for recording (capture)
    if ((pcm = snd_pcm_open(&pcm_handle, PCM_DEVICE, SND_PCM_STREAM_CAPTURE, 0)) < 0) {
        fprintf(stderr, "ERROR: Can't open \"%s\" PCM device. %s\n", PCM_DEVICE, snd_strerror(pcm));
        return -1;
    }

    // Allocate parameters object and fill it with default values
    snd_pcm_hw_params_alloca(&params);
    snd_pcm_hw_params_any(pcm_handle, params);

    // Set parameters
    snd_pcm_hw_params_set_access(pcm_handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);
    snd_pcm_hw_params_set_format(pcm_handle, params, SND_PCM_FORMAT_S16_LE);
    snd_pcm_hw_params_set_channels(pcm_handle, params, channels);
    snd_pcm_hw_params_set_rate_near(pcm_handle, params, &rate, 0);

    // Write parameters
    if ((pcm = snd_pcm_hw_params(pcm_handle, params)) < 0) {
        fprintf(stderr, "ERROR: Can't set hardware parameters. %s\n", snd_strerror(pcm));
        return -1;
    }

    // Capture audio and calculate dB level
    while (1) {
    	//printf("\033[H\033[J");
        if ((pcm = snd_pcm_readi(pcm_handle, buffer, BUFFER_SIZE)) == -EPIPE) {
            fprintf(stderr, "XRUN.\n");
            snd_pcm_prepare(pcm_handle);
        } else if (pcm < 0) {
            fprintf(stderr, "ERROR: Can't read from PCM device. %s\n", snd_strerror(pcm));
        } else {
            double sum = 0.0;
            for (int i = 0; i < BUFFER_SIZE; i++) {
                sum += buffer[i] * buffer[i];
            }
            double rms = sqrt(sum / BUFFER_SIZE);
            double db = 20 * log10(rms);
            printf("dB Level: %.2f\n", db);
        }
    }

    snd_pcm_close(pcm_handle);
    return 0;
}

