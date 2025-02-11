/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:39:37 by jaubry--          #+#    #+#             */
/*   Updated: 2025/02/11 18:02:12 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "osci.h"

/*
	Debug function that draws ontop of the main oscilloscope, on the
	left top the left channel and just under, the right channel
	This oscilloscope reprents value as y coordinates and
	x is the time.
*/
static void	draw_osci_side(t_env *env, t_vec2 half, t_vec2 quarter, int channel)
{
	size_t	i;
	int		x;
	int		y;
	int		half_buf;
	int		offset;

	offset = quarter.y + (half.y * channel);
	half_buf = (env->buf_len / 2);
	i = 0;
	while (i < env->buf_len)
	{
		x = ((float)i / half_buf) * quarter.x;
		y = offset - (quarter.y * ((float)env->buffer[i + channel] / MAXPCM));
		ft_mlx_pixel_put(&env->mlx->img, new_vec2(x, y), 0xFF0000);
		i += 2;
	}
}

static void	draw_debug(t_env *env)
{
	draw_osci_side(env, env->mlx->half, env->mlx->quarter, 0);
	draw_osci_side(env, env->mlx->half, env->mlx->quarter, 1);
}

/*
	Function that draws the oscilloscope parsing the PCM audio buffer.
	The data is stored in a way we get each channels sample then the next
	sample. We use the left channel to plot the x axis and the right for the y
	axis.
*/
static void	draw_osci(t_env *env)
{
	t_mlx	*mlx;
	size_t	i;
	t_vec2	pos;

	i = 0;
	mlx = env->mlx;
	pthread_mutex_lock(&env->buffer_mutex);
	if (DEBUG)
		draw_debug(env);
	if (RAINBOW && ((mlx->tick % 10) == 0))
		rainbow_transition(&mlx->color);
	while (i < env->buf_len)
	{
		pos = (t_vec2)
		{
			mlx->half.x - (mlx->half.x * ((float)(env->buffer[i]) / MAXPCM)),
			mlx->half.y - (mlx->half.y * ((float)(env->buffer[i + 1]) / MAXPCM))
		};
		ft_mlx_pixel_put(&env->mlx->img, pos, env->mlx->color);
		i += 2;
	}
	pthread_mutex_unlock(&env->buffer_mutex);
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
	t_mlx	*mlx;

	mlx = env->mlx;
	mlx->tick += 1;
	pthread_mutex_lock(&g_stop_mutex);
	if (g_stop)
	{
		pthread_mutex_unlock(&g_stop_mutex);
		mlx_loop_end(mlx->mlx);
	}
	else
		pthread_mutex_unlock(&g_stop_mutex);
	if (GLASS)
	{
		kill_img(mlx->mlx, &mlx->img);
		mlx->img = init_img(mlx->mlx, WIDTH, HEIGHT);
		if (!mlx->img.img || !mlx->img.addr)
			return (1);
	}
	else
		ft_mlx_batch_put(&mlx->img, mlx->origin, mlx->size, BACKGROUND);
	draw_osci(env);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	return (0);
}
