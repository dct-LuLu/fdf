/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   osci.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:39:37 by jaubry--          #+#    #+#             */
/*   Updated: 2025/02/01 12:42:56 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
	Ideas and potentiels problems to fix the osci visibility issues:

	- Try to make opacity work to have some kind of afterglow

	- Implement some bigger oscilloscope dot (not a single pixel, make a square or a circle)

	- Try implementing triple buffering to reduce potential tearing caused by MLX (the issue could be also that the draw function has not enough time to read and draw using the audio buffer because not fast enough? Mutex may also cause somes issues)


*/

void	draw_osci_side(t_env env, t_vec2 half, int channel)
{
	size_t	i;
	t_vec2	pos;
	t_vec2	quarter;

	quarter = (t_vec2){half.x / 2, half.y / 2};
	i = 0;
	while (i < buf_len)
	{
		pos = new_vec2(
			((float)i / (buf_len / 2)) * quarter.x,
			(quarter.y - (quarter.y * ((float)(buffer[i + channel]) / MAX_SAMPLE))) + (half.y * channel)
				);
		unsigned int color = (0x10 << 24) | (0xFF << 16) | (0x00 << 8) | 0x00;
		ft_mlx_pixel_put(&env.img, pos, color);
		i += 2;
	}
}

void	draw_osci(t_env env)
{
    size_t  i;
    t_vec2  pos;
    t_vec2	half;
    /*
    t_vec2  old;

    old.x = 0;
    old.y = 0;
    */
    half = (t_vec2){env.img.width / 2, env.img.height / 2};
    i = 0;
    pthread_mutex_lock(&audio_mutex);
    if (DEBUG)
    {
	    draw_osci_side(env, half, 0);
    	draw_osci_side(env, half, 1);
    }
    while (i < buf_len)
    {
        pos = new_vec2(
            half.x - (half.x * ((float)(buffer[i]) / MAX_SAMPLE)),
            half.y - (half.y * ((float)(buffer[i + 1]) / MAX_SAMPLE))
        );
        
        //if (old.x && old.y)
        //    ft_mlx_line_put(&env.img, old, pos, argb(255, 0, 255, 0));
        //old = pos;

        unsigned int color = (0x10 << 24) | (0x00 << 16) | (0xFF << 8) | 0x00;
        ft_mlx_pixel_put(&env.img, pos, color);
        i += 2;
    }
    pthread_mutex_unlock(&audio_mutex);
}
