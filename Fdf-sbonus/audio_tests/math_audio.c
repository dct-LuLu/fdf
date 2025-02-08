/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_audio.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:42:39 by jaubry--          #+#    #+#             */
/*   Updated: 2025/02/08 01:07:06 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "audio_tests.h"
#include <math.h>

/*
	Function that computes the RMS using the PCM signal for the given channel.
*/
double	compute_rms(int16_t *buffer, size_t buf_len, int channel_i)
{
	double	normalized_sample;
	double	rms;
	size_t	i;

	i = 0;
	rms = 0.0f;
	while (i < buf_len)
	{
		normalized_sample = buffer[i + channel_i] / MAX_SAMPLE;
		rms += normalized_sample * normalized_sample;
		i += CHANNELS;
	}
	return (sqrt(rms / (buf_len / CHANNELS)));
}

/*
	Function that computes the peak dB using the PCM signal for
	the given channel.
*/
double	peak_db(int16_t *buffer, size_t buf_len, int channel_i)
{
	int		abs_sample;
	int		peak;
	size_t	i;

	i = 0;
	peak = 0;
	while (i < buf_len)
	{
		abs_sample = abs(buffer[i + channel_i]);
		if (abs_sample > peak)
			peak = abs_sample;
		i += CHANNELS;
	}
	return (20 * log10((double)peak / MAX_SAMPLE));
}

/*
	Function that computes the dBFS from rms
*/
double	convert_dbfs(double rms)
{
	return (20 * log10(rms));
}
