/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rainbow.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 19:48:44 by jaubry--          #+#    #+#             */
/*   Updated: 2025/02/11 17:00:00 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAINBOW_H
# define RAINBOW_H
# ifndef HUE_SPEED
#  define HUE_SPEED 1
# endif

// RGB
# define R 0 // Red
# define G 1 // Green
# define B 2 // Blue

// HSV
# define H 0 // Hue
# define S 1 // Saturation
# define V 2 // Value

// HSV to RGB conversion variables
# define C 0 // Chroma
# define X 1 // Secondary Component
# define M 2 // Match Value

void	rainbow_transition(unsigned int *argb);

#endif // RAINBOW_H
