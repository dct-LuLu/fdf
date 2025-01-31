/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   osci.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:39:37 by jaubry--          #+#    #+#             */
/*   Updated: 2025/01/31 14:45:02 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_osci(t_env env)
{
    size_t  i;
    int half_w;
    int half_h;
    t_vec2  pos;
    /*
    t_vec2  old;

    old.x = 0;
    old.y = 0;
    */
    half_w = env.img.width / 2;
    half_h = env.img.height / 2;
    i = 0;
    pthread_mutex_lock(&audio_mutex);
    while (i < buf_len)
    {
        pos = new_vec2(
            half_w - (half_w * ((float)(buffer[i]) / MAX_SAMPLE)),
            half_h - (half_h * ((float)(buffer[i + 1]) / MAX_SAMPLE))
        );
        /*
        if (old.x && old.y)
        {
            ft_mlx_line_put(&env.img, old, pos, argb(255, 0, 255, 0));
        }
        old = pos;
        */
        ft_mlx_pixel_put(&env.img, pos, argb(0, 255, 0, 0));
        i += 2;
    }
    pthread_mutex_unlock(&audio_mutex);
}
