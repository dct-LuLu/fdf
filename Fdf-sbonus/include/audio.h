/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:34:02 by jaubry--          #+#    #+#             */
/*   Updated: 2025/02/11 18:01:22 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUDIO_H
# define AUDIO_H
# include <pulse/pulseaudio.h>
# include <pulse/thread-mainloop.h>
# include <inttypes.h>
# define SAMPLE_RATE 192000
# define MAXPCM 32768.0 // Max absolute sample
# define CHANNELS 2
# define BUFFER_DURATION_MS 1
# define DEVICE "alsa_output.usb-GuangZhou_FiiO_Electronics_Co._Ltd_FiiO_K7-00\
.analog-stereo.monitor"
# define UNDEF 0xFFFFFFFF // ((uint32_t) - 1)

typedef struct s_pa
{
	pa_threaded_mainloop	*loop;
	pa_mainloop_api			*api;
	pa_context				*ctx;
	pa_stream				*stream;
}	t_pa;

void	context_state_callback(pa_context *c, void *userdata);

#endif// AUDIO_H
