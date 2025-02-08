/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_audio.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:42:39 by jaubry--          #+#    #+#             */
/*   Updated: 2025/02/08 01:22:10 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "audio_tests.h"
#include <stdio.h>

/*
	Function to display dB peaks on full scale MAX_DB MIN_DB
*/
static void	display_dbfs_gauge(double peak_dbfs)
{
	size_t	num_bars;
	double	range;
	double	scale;
	size_t	i;

	range = MAX_DB - MIN_DB;
	scale = (peak_dbfs - MIN_DB) / range;
	num_bars = (size_t)(scale * GAUGE_WIDTH);
	if (peak_dbfs < MIN_DB)
		num_bars = 0;
	printf("[");
	i = 0;
	while (i < GAUGE_WIDTH)
	{
		if (i < num_bars)
			printf("#");
		else
			printf(" ");
		i++;
	}
	printf("] %.2f peak dBFS\n", peak_dbfs);
}

/*
	Function that display the Pulse Code Modulation of
	the audio stream
*/
static void	display_pcm(int16_t *data, size_t buf_len)
{
	size_t	i;

	i = 0;
	printf("\n\nPCM SIGNAL: %zu\n", buf_len);
	while (i < buf_len)
	{
		printf("%d\t", data[i]);
		if ((i + 1) % 24 == 0)
			printf("\n");
		i++;
	}
}

/*
	Function that displays, RMS, dBFS, peak dBFS and its jauges
*/
static void	display_info(int16_t *data, size_t buf_len)
{
	double	rms;
	double	peak;
	size_t	i;

	i = 0;
	printf("\033[H\033[J");
	while (i < 2)
	{
		rms = compute_rms(data, buf_len, i);
		peak = peak_db(data, buf_len, i);
		printf("F%c: %.2fRMS\t%.2fdBFS\n", "LR"[i], rms, convert_dbfs(rms));
		display_dbfs_gauge(peak);
		printf("\n\n");
		i++;
	}
}

/*
	Function that prints on the terminal the audio data
	Will print the pcm code with DEBUG mode
*/
void	display_audio(int16_t *data, size_t buf_len)
{
	display_info(data, buf_len);
	if (DEBUG == 1)
		display_pcm(data, buf_len);
}
