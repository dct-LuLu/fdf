/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rainbow.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:39:37 by jaubry--          #+#    #+#             */
/*   Updated: 2025/02/10 18:32:38 by jaubry--         ###   ########.fr       */
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
	hsv[H] = fmodf(hsv[H], 6.0f);
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
	float	rgb[3];

	rgb[R] = ((argb >> 16) & 0xFF) / 255.0f;
	rgb[G] = ((argb >> 8) & 0xFF) / 255.0f;
	rgb[B] = (argb & 0xFF) / 255.0f;
	hsv_calculation(hsv, rgb);
}

/*
	Find each sector colors for R, G, B to set cxm values.
*/
static void	apply_sector(float hsv[3], float rgb[3], float cxm[3])
{
	int	sector;

	sector = (int)(hsv[H] / 60);
	if ((sector == 0) || (sector == 5))
		rgb[R] = cxm[C];
	else if ((sector == 1) || (sector == 4))
		rgb[R] = cxm[X];
	else
		rgb[R] = 0;
	if ((sector == 1) || (sector == 2))
		rgb[G] = cxm[C];
	else if ((sector == 0) || (sector == 3))
		rgb[G] = cxm[X];
	else
		rgb[G] = 0;
	if ((sector == 3) || (sector == 4))
		rgb[B] = cxm[C];
	else if ((sector == 2) || (sector == 5))
		rgb[B] = cxm[X];
	else
		rgb[B] = 0;
}

/*
	Function that converts argb to hsv
*/
static unsigned int	hsv_to_argb(float hsv[3], unsigned int alpha)
{
	float	rgb[3];
	float	cxm[3];

	cxm[C] = hsv[V] * hsv[S];
	cxm[X] = cxm[C] * (1 - fabsf(fmodf(hsv[H] / 60.0f, 2) - 1));
	cxm[M] = hsv[V] - cxm[C];
	apply_sector(hsv, rgb, cxm);
	rgb[R] += cxm[M];
	rgb[G] += cxm[M];
	rgb[B] += cxm[M];
	return (((int)(rgb[R] * 255) << 16) | ((int)(rgb[G] * 255) << 8)
			| ((int)(rgb[B] * 255)) | alpha);
}

/*
	Increment the argb value with the hue speed by transforming it into
	hsv value to easily add to the 360 degree wide, Hue attribute.
*/
void	rainbow_transition(unsigned int *argb)
{
	unsigned int	alpha;
	float			hsv[3];

	alpha = ((*argb) >> 24) & 0xFF;
	argb_to_hsv(*argb, hsv);
	hsv[H] += HUE_SPEED;
	if (hsv[H] >= 360.0f)
		hsv[H] -= 360;
	*argb = hsv_to_argb(hsv, alpha);
}
