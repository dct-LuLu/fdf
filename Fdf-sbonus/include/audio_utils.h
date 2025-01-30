/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:46:35 by jaubry--          #+#    #+#             */
/*   Updated: 2025/01/29 18:23:58 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUDIO_UTILS_H
# define AUDIO_UTILS_H
/*
# include <pulse/simple.h>
# include <pulse/error.h>
# define SAMPLE_RATE 48000
# define CHANNELS 2
# define BUFFER_DURATION_MS 2
# define MAX_SAMPLE 32768.0
# define DEVICE "alsa_output.usb-GuangZhou_FiiO_Electronics_Co._Ltd_FiiO_K7-00.analog-stereo.monitor"
*/
/*
    defined based on PA_SAMPLE_S16LE, Signed 16 integer bit PCM, little endian.
    values ranging from -32768 to 32767
*/
/*
typedef struct s_pa
{
    pa_simple       *serv;
    size_t          buf_len;
    size_t          buf_size;
    int16_t         *stream;
    int             error;
}	t_pa;

t_pa	*init_pa(void);

void	snap_stream(t_pa *pa);

void	kill_audio(t_pa *pa);
*/
#endif //AUDIO_UTILS_H
