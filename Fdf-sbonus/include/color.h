/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 19:48:44 by jaubry--          #+#    #+#             */
/*   Updated: 2025/02/07 01:06:39 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

typedef struct s_color
{
	unsigned int	a;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
}	t_color;

/*
t_color	new_color(unsigned int a, unsigned int r, unsigned int g, unsigned int b);

t_color	color_rgb(unsigned int color);

t_color	color_argb(unsigned int color);

unsigned int	int_rgb(t_color color);
unsigned int	int_argb(t_color color);
*/


#endif
