/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_alsa_5s_bass.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:48:12 by jaubry--          #+#    #+#             */
/*   Updated: 2025/01/22 17:41:42 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <errno.h>
#include <string.h>
#include <math.h>
#include <alsa/asoundlib.h>

#define AMPLITUDE 32767    // Max amplitude for 16-bit audio
#define FREQUENCY 80.0    // Frequency of the sine wave (Hz)
#define DURATION 7         // Duration of the sound in seconds (5 seconds)

int main() {
	unsigned int	SAMPLE_RATE = 44100;
    snd_pcm_t *pcm_handle;
    snd_pcm_hw_params_t *params;
    short sample;
    int num_samples = SAMPLE_RATE * DURATION;  // Total samples based on duration and sample rate
    double phase_increment = 2.0 * M_PI * FREQUENCY / SAMPLE_RATE; // Increment for sine wave

    // Open the PCM device for playback
    if (snd_pcm_open(&pcm_handle, "default", SND_PCM_STREAM_PLAYBACK, 0) < 0)
        return (perror("PCM open failed"), 1);

    // Allocate hardware parameters object
    snd_pcm_hw_params_alloca(&params);

    // Set the desired hardware parameters
    snd_pcm_hw_params_any(pcm_handle, params);
    snd_pcm_hw_params_set_access(pcm_handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);
    snd_pcm_hw_params_set_format(pcm_handle, params, SND_PCM_FORMAT_S16_LE);  // 16-bit signed little-endian
    snd_pcm_hw_params_set_rate_near(pcm_handle, params, &SAMPLE_RATE, 0);
    snd_pcm_hw_params_set_channels(pcm_handle, params, 1);  // Mono

    // Apply the hardware parameters
    if (snd_pcm_hw_params(pcm_handle, params) < 0)
	    return (perror("Setting HW params failed"), snd_pcm_close(pcm_handle), 1);

	int	i;

	i = 0;
	while (i < num_samples)
	{
        sample = (short)(AMPLITUDE * sin(i * phase_increment));

        // Write the sample to the ALSA playback buffer
        if (snd_pcm_writei(pcm_handle, &sample, 1) < 0)
			return (perror("Error writing to PCM device"), snd_pcm_close(pcm_handle), 1);
        i++;
    }
    snd_pcm_drain(pcm_handle);

    snd_pcm_close(pcm_handle);
    return (0);
}

