/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_tests.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:46:35 by jaubry--          #+#    #+#             */
/*   Updated: 2025/02/08 01:24:18 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUDIO_TESTS_H
# define AUDIO_TESTS_H
# include <pulse/pulseaudio.h>
# include <inttypes.h>
# include <pthread.h>
# include "libft.h"
# define SAMPLE_RATE 48000
# define CHANNELS 2
# define BUFFER_DURATION_MS 1
# define GAUGE_WIDTH 120
# define MIN_DB -60 // Minimum dBFS (-inf/silence/lowest visible level)
# define MAX_DB 0 // Maximum dBFS (0 dBFS/the maximum level)
# define MAX_SAMPLE 32768.0
# ifndef DEVICE
#  define DEVICE "alsa_output.usb-GuangZhou_FiiO_Electronics_Co._Ltd_FiiO_K7-00\
.analog-stereo.monitor"
# endif
# ifndef DEBUG
#  define DEBUG 0
# endif

typedef struct s_pa
{
	pa_mainloop		*loop;
	pa_mainloop_api	*api;
	pa_context		*ctx;
	pa_stream		*stream;
}	t_pa;

double	compute_rms(int16_t *buffer, size_t buf_len, int channel_i);
double	peak_db(int16_t *buffer, size_t buf_len, int channel_i);
double	convert_dbfs(double rms);

void	display_audio(int16_t *data, size_t buf_len);

void	context_state_callback(pa_context *c, void *userdata);

#endif //AUDIO_TESTS_H
