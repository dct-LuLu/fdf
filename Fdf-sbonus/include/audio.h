/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:34:02 by jaubry--          #+#    #+#             */
/*   Updated: 2025/02/10 21:40:39 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUDIO_H
# define AUDIO_H
# define SAMPLE_RATE 192000
# define CHANNELS 2
# define BUFFER_DURATION_MS 1
# define DEVICE "alsa_output.usb-GuangZhou_FiiO_Electronics_Co._Ltd_FiiO_K7-00\
.analog-stereo.monitor";
# define UNDEF ((uint32_t) - 1)

typedef struct s_pa
{
	pa_threaded_mainloop	*loop;
	pa_mainloop_api			*api;
	pa_context				*ctx;
	pa_stream				*stream;
	pthread_mutex_t			audio_mutex;
	int16_t					*buffer;
	size_t					buf_len;
}	t_pa;

#endif// AUDIO_H
