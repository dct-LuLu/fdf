/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_tests.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:46:35 by jaubry--          #+#    #+#             */
/*   Updated: 2025/02/06 21:01:23 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUDIO_TESTS_H
# define AUDIO_TESTS_H
# define SAMPLE_RATE 48000
# define CHANNELS 2
# define BUFFER_DURATION_MS 1
# define GAUGE_WIDTH 120
# define MIN_DB -60 // Minimum dBFS (-inf/silence/lowest visible level)
# define MAX_DB 0 // Maximum dBFS (0 dBFS/the maximum level)
# define MAX_SAMPLE 32768.0
# define DEVICE "alsa_output.usb-GuangZhou_FiiO_Electronics_Co._Ltd_FiiO_K7-00\
.analog-stereo.monitor"

typedef struct s_pa
{
	pa_mainloop		*loop;
	pa_mainloop_api	*api;
	pa_context		*ctx;
	pa_stream		*stream;
}	t_pa;


#endif //AUDIO_TESTS_H
