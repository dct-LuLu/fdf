/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 19:47:14 by jaubry--          #+#    #+#             */
/*   Updated: 2025/02/05 21:34:57 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

// Optimized new_color function
t_color new_color(unsigned int a, unsigned int r, unsigned int g, unsigned int b)
{
    return (t_color){a, r, g, b}; // Direct initialization using a compound literal
}

// Optimized color_rgb function
t_color color_rgb(unsigned int color)
{
    // Directly assign fields using bit shifts and masks
    return (t_color){0xFF, (color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF};
}

// Optimized color_argb function
t_color color_argb(unsigned int color)
{
    // Directly assign fields using bit shifts and masks
    return (t_color){(color >> 24) & 0xFF, (color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF};
}

// Optimized int_rgb function
unsigned int int_rgb(t_color color)
{
    // Combine the RGB values into an unsigned int
    return (color.r << 16) | (color.g << 8) | color.b;
}

// Optimized int_argb function
unsigned int int_argb(t_color color)
{
    // Combine the ARGB values into an unsigned int
    return (color.a << 24) | (color.r << 16) | (color.g << 8) | color.b;
}

