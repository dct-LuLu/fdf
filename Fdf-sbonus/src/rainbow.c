/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rainbow.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:39:37 by jaubry--          #+#    #+#             */
/*   Updated: 2025/02/08 08:01:28 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "rainbow.h"
#include <math.h>

/*
	Function that computes the hue, the saturation and the value from rgb. 
*/
static void	hsv_calculation(float hsv[3], float rgb[3])
{
	float	cmax;
	float	cmin;
	float	diff;

	cmax = fmaxf(fmaxf(rgb[R], rgb[G]), rgb[B]);
	cmin = fminf(fminf(rgb[R], rgb[G]), rgb[B]);
	diff = cmax - cmin;
	if (diff == 0)
		hsv[H] = 0;
    else if (cmax == rgb[R])
		hsv[H] = fmodf((rgb[G] - rgb[B]) / diff, 6.0f);
    else if (cmax == rgb[G])
		hsv[H] = (rgb[B] - rgb[R]) / diff + 2.0f;
    else
		hsv[H] = (rgb[R] - rgb[G]) / diff + 4.0f;
	hsv[H] = fmodf(hsv[H], 6.0f); // ?
    if (hsv[H] < 0)
		hsv[H] += 6.0f;
    hsv[H] *= 60.0f;
	if (cmax == 0)
		hsv[S] = 0;
    else
		hsv[S] = diff / cmax;
    hsv[V] = cmax;
}

/*
	Function that transform argb to hsv.
*/
static void	argb_to_hsv(unsigned int argb, float hsv[3])
{
    float rgb[3];
	
	rgb[R] = ((argb >> 16) & 0xFF) / 255.0f;
	rgb[G] = ((argb >> 8) & 0xFF) / 255.0f;
	rgb[B] = (argb & 0xFF) / 255.0f;
	hsv_calculation(hsv, rgb);
}


static unsigned int	hsv_to_argb(float hsv[3], unsigned int alpha)
{
    float	rgb[3];
	float	c;
	float	x;
	float	m;

    c = hsv[V] * hsv[S];
    x = c * (1 - fabsf(fmodf(hsv[H] / 60.0f, 2) - 1));
    m = hsv[V] - c;

	int	sector = (int)(hsv[H] / 60);
	if ((sector == 0) || (sector == 5))
		rgb[R] = c;
	else if ((sector == 1) || (sector == 4))
		rgb[R] = x;
	else
		rgb[R] = 0;

	if ((sector == 1) || (sector == 2))
		rgb[G] = c;
	else if ((sector == 0) || (sector == 3))
		rgb[G] = x;
	else
		rgb[G] = 0;

	if ((sector == 3) || (sector == 4))
		rgb[B] = c;
	else if ((sector == 2) || (sector == 5))
		rgb[B] = x;
	else
		rgb[B] = 0;

    rgb[R] += m;
    rgb[G] += m;
    rgb[B] += m;
    return (((int)(rgb[R] * 255) << 16) | ((int)(rgb[G] * 255) << 8) | ((int)(rgb[B] * 255)) | alpha);
}
#include <stdio.h>
void rainbow_transition(unsigned int *argb, unsigned int hue_increment)
{
	unsigned int	alpha;
    float			hsv[3];

	printf("Before: argb =\t\t%d\n", *argb);
	alpha = ((*argb) >> 24) & 0xFF;
    argb_to_hsv(*argb, hsv);
	printf("Before: hsv[H] =\t%.2f\n", hsv[H]);
    hsv[H] += hue_increment;
	printf("Middle: hsv[H] =\t%.2f\n", hsv[H]);
    if (hsv[H] >= 360.0f)
		hsv[H] -= 360;
    *argb = hsv_to_argb(hsv, alpha);
	printf("After: hsv[H] =\t\t%.2f\n", hsv[H]);
	printf("After: argb =\t\t%d\n\n", *argb);
}