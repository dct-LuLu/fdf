/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:39:37 by jaubry--          #+#    #+#             */
/*   Updated: 2025/02/10 20:19:16 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
	Debug function that draws ontop of the main oscilloscope, on the
	left top the left channel and just under, the right channel
	This oscilloscope reprents value as y coordinates and
	x is the time.
*/
static void	draw_osci_side(t_env env, t_vec2 half, t_vec2 quarter, int channel)
{
	size_t	i;
	int		x;
	int		y;
	int		half_buf;
	int		offset;

	offset = quarter.y + (half.y * channel);
	half_buf = (buf_len / 2);
	i = 0;
	while (i < buf_len)
	{
		x = ((float)i / half_buf) * quarter.x;
		y = offset - (quarter.y * ((float)buffer[i + channel] / MAX_SAMPLE));
		ft_mlx_pixel_put(&env.img, new_vec2(x, y), 0xFF0000);
		i += 2;
	}
}

/*
	Function that draws the oscilloscope parsing the PCM audio buffer.
	The data is stored in a way we get each channels sample then the next
	sample. We use the left channel to plot the x axis and the right for the y
	axis.
*/
static void	draw_osci(t_env *env)
{
	size_t	i;
	t_vec2	pos;

	i = 0;
	pthread_mutex_lock(&audio_mutex);
	if (DEBUG)
	{
		draw_osci_side(*env, env->half, env->quarter, 0);
		draw_osci_side(*env, env->half, env->quarter, 1);
	}
	if (RAINBOW && ((env->tick % 10) == 0))
		rainbow_transition(&env->color);
	while (i < buf_len)
	{
		pos = (t_vec2)
		{
			env->half.x - (env->half.x * ((float)(buffer[i]) / MAX_SAMPLE)),
			env->half.y - (env->half.y * ((float)(buffer[i + 1]) / MAX_SAMPLE))
		};
		ft_mlx_pixel_put(&env->img, pos, env->color);
		i += 2;
	}
	pthread_mutex_unlock(&audio_mutex);
}

/*
	Routine that checks if stop signal is true, draws and update the window
	depending on the mode (will kill and reinit if GLASS mode or will add
	to the foreground some black squarte with a little opacity to mimic 
	afterglow effect).
	And will draw the oscilloscope on the image and then put the image on
	the window.
*/
int	draw_routine(t_env *env)
{
	env->tick += 1;
	pthread_mutex_lock(&stop_mutex);
	if (stop)
	{
		pthread_mutex_unlock(&stop_mutex);
		mlx_loop_end(env->mlx);
	}
	else
		pthread_mutex_unlock(&stop_mutex);
	if (GLASS)
	{
		kill_img(env->mlx, &env->img);
		env->img = init_img(env->mlx, WIDTH, HEIGHT);
		if (!env->img.img || !env->img.addr)
			return (1);
	}
	else
		ft_mlx_batch_put(&env->img, env->origin, env->size, BACKGROUND);
	draw_osci(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img.img, 0, 0);
	return (0);
}
