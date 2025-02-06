/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   osci.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:39:37 by jaubry--          #+#    #+#             */
/*   Updated: 2025/02/06 23:51:24 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
	Ideas and potentiels problems to fix the osci visibility issues:

	- Try to make opacity work to have some kind of afterglow

	- Implement some bigger oscilloscope dot (not a single pixel, make a square or a circle)

	- Try implementing triple buffering to reduce potential tearing caused by MLX (the issue could be also that the draw function has not enough time to read and draw using the audio buffer because not fast enough? Mutex may also cause somes issues)


*/

t_vec2	half = (t_vec2){WIDTH / 2, HEIGHT / 2};
t_vec2	quarter = (t_vec2){WIDTH / 4, HEIGHT / 4};

void	draw_osci_side(t_env env, t_vec2 half, int channel)
{
	size_t	i;
	t_vec2	pos;

	i = 0;
	while (i < buf_len)
	{
		pos = new_vec2(
			((float)i / (buf_len / 2)) * quarter.x,
			(quarter.y - (quarter.y * ((float)(buffer[i + channel]) / MAX_SAMPLE))) + (half.y * channel)
				);
//unsigned int color = (0x10 << 24) | (0xFF << 16) | (0x00 << 8) | 0x00;
		ft_mlx_pixel_put(&env.img, pos, 0xFF0000);
		i += 2;
	}
}

#include <math.h>

// Function to convert ARGB to HSV
void argb_to_hsv(unsigned int argb, float* h, float* s, float* v)
{
    float r = ((argb >> 16) & 0xFF) / 255.0f;
    float g = ((argb >> 8) & 0xFF) / 255.0f;
    float b = (argb & 0xFF) / 255.0f;

    float cmax = fmaxf(fmaxf(r, g), b);
    float cmin = fminf(fminf(r, g), b);
    float diff = cmax - cmin;

    // Hue calculation
    if (diff == 0) *h = 0;
    else if (cmax == r) *h = fmodf((g - b) / diff, 6.0f);
    else if (cmax == g) *h = (b - r) / diff + 2.0f;
    else *h = (r - g) / diff + 4.0f;

    if (*h < 0) *h += 6.0f;

    *h *= 60.0f;

    // Saturation calculation
    if (cmax == 0) *s = 0;
    else *s = diff / cmax;

    // Value calculation
    *v = cmax;
}

// Function to convert HSV back to ARGB
unsigned int hsv_to_argb(float h, float s, float v)
{
    float c = v * s;
    float x = c * (1 - fabsf(fmodf(h / 60.0f, 2) - 1));
    float m = v - c;

    float r, g, b;
    if (0 <= h && h < 60) { r = c; g = x; b = 0; }
    else if (60 <= h && h < 120) { r = x; g = c; b = 0; }
    else if (120 <= h && h < 180) { r = 0; g = c; b = x; }
    else if (180 <= h && h < 240) { r = 0; g = x; b = c; }
    else if (240 <= h && h < 300) { r = x; g = 0; b = c; }
    else { r = c; g = 0; b = x; }

    r += m;
    g += m;
    b += m;

    return ((int)(r * 255) << 16) | ((int)(g * 255) << 8) | ((int)(b * 255)) | 0xFF000000;
}

// Function to smoothly transition through the rainbow spectrum
void rainbow_transition(unsigned int* argb, float hue_increment)
{
    float h, s, v;

    // Convert current ARGB to HSV
    argb_to_hsv(*argb, &h, &s, &v);

    // Increment hue and ensure it wraps around
    h += hue_increment;
    if (h >= 360.0f) h -= 360.0f;

    // Convert back to ARGB
    *argb = hsv_to_argb(h, s, v);
}

unsigned int color = 0xFF0000FF; // Starting with pure red (ARGB format)
float hue_increment = 0.3f; // Change the hue by 1 degree each time

// Transition the color

void	draw_osci(t_env env)
{
    size_t  i;
    t_vec2  pos;
    /*
    t_vec2  old;

    old.x = 0;
    old.y = 0;
    */
    i = 0;
    pthread_mutex_lock(&audio_mutex);
    if (DEBUG)
    {
	    draw_osci_side(env, half, 0);
    	draw_osci_side(env, half, 1);
    }
	if (RAINBOW)
    	rainbow_transition(&color, hue_increment);
    while (i < buf_len)
    {
        pos = new_vec2(
            half.x - (half.x * ((float)(buffer[i]) / MAX_SAMPLE)),
            half.y - (half.y * ((float)(buffer[i + 1]) / MAX_SAMPLE))
        );
        
        //if (old.x && old.y)
        //    ft_mlx_line_put(&env.img, old, pos, argb(255, 0, 255, 0));
        //old = pos;
	
        ft_mlx_pixel_put(&env.img, pos, 0x00FF00FF);
        i += 2;
    }
    pthread_mutex_unlock(&audio_mutex);
}
