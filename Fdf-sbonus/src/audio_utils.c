/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:46:35 by jaubry--          #+#    #+#             */
/*   Updated: 2025/01/28 13:10:14 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "audio_utils.h"
#include "libft.h"

t_pa    *init_pa(void)
{
    static const pa_sample_spec ss = {
        .format = PA_SAMPLE_S16LE, 
        .rate = SAMPLE_RATE,
        .channels = CHANNELS
    };
    t_pa    *pa;

    pa = ft_calloc(1, sizeof(t_pa));
    if (!pa)
        return (NULL);
    pa->serv = pa_simple_new(NULL, "AudioMonitor", PA_STREAM_RECORD, DEVICE, "record", &ss, NULL, NULL, &pa->error);
    if (!pa->serv)
    {
        ft_dprintf(STDERR_FILENO, "pa_simple_new() failed: %s\n", pa_strerror(pa->error));
        free(pa);
        return (NULL);
    }
    pa->buf_len = (SAMPLE_RATE * CHANNELS * BUFFER_DURATION_MS / 1000);
    pa->buf_size = pa->buf_len * sizeof(int16_t);
    pa->stream = malloc(pa->buf_size);
    if (!pa->stream)
        return (free(pa), NULL);
    return (pa);
}

/*
    Function that will take "snapshot" of the current audio stream.
    Will sample BUFFER_DURATION_MS samples
*/
void    snap_stream(t_pa *pa)
{
    int ret;

    ret = pa_simple_read(pa->serv, pa->stream, pa->buf_size, &pa->error);
    if (ret < 0)
        ft_dprintf(STDERR_FILENO, "pa_simple_read() failed: %s\n", pa_strerror(pa->error));
}

/*
    Function to free all necessary part for audio
*/
void    kill_audio(t_pa *pa)
{
    free(pa->stream);
    pa_simple_free(pa->serv);
    free(pa);
}

/*
#include <stdio.h>
void    print_samples(t_pa *pa)
{
    size_t  i;

    printf("\033[H\033[J");
    printf("PCM SIGNAL:\n");
    i = 0;
    while (i < pa->buf_len)
    {
        printf("%d\t", pa->stream[i]);
        if (((i + 1) % 8) == 0)
            printf("\n");
        i++;
    }
    printf("\n\n");
}

int main(void)
{
    t_pa    *pa;

    pa = init_pa();
    if (!pa)
        return (EXIT_FAILURE);

    snap_stream(pa);
    //print_samples(pa);
    kill_audio(pa);
    return (EXIT_SUCCESS);
}
*/
