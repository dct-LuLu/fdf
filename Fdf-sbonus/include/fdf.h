/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 01:04:16 by jaubry--          #+#    #+#             */
/*   Updated: 2025/02/10 21:32:50 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft.h"
# include <mlx.h>
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "vec2.h"
# ifndef WIDTH
#  define WIDTH 500
# endif
# ifndef HEIGHT
#  define HEIGHT 500
# endif
# ifndef DEBUG
#  define DEBUG 0
# endif
# ifndef RAINBOW
#  define RAINBOW 0
# endif

# include <signal.h>
# include <pthread.h>
# define MAX_SAMPLE 32768.0
# define BACKGROUND 0x0F000000
# define DOT 0x0000FF19 //GREEN BLUEISH
//# define COLOR 0x00A92299 //PINK

# ifndef HUE_SPEED
#  define HUE_SPEED 1
# endif
extern pthread_mutex_t			stop_mutex; 
extern volatile sig_atomic_t	stop;
extern pthread_mutex_t			audio_mutex;
extern int16_t					*buffer;
extern size_t					buf_len;

typedef struct s_pa
{
	pa_threaded_mainloop	*loop;
	pa_mainloop_api			*api;
	pa_context				*ctx;
	pa_stream				*stream;
	pthread_mutex_t			audio_mutex;
	int16_t					*buffer;
	size_t					buf_len;
}	t_pa;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		byte_depth;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_env
{
	void			*mlx;
	void			*win;
	t_img			img;
	t_vec2			origin;
	t_vec2			size;
	size_t			tick;
	t_vec2			half;
	t_vec2			quarter;
	unsigned int	color;
}	t_env;

typedef struct s_line
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;
}	t_line;

void	rainbow_transition(unsigned int* argb);

int		abs(int x);

t_img	init_img(void *mlx, int width, int height);
void	ft_mlx_pixel_put(t_img *data, t_vec2 pos, int color);
void	ft_mlx_line_put(t_img *data, t_vec2 a, t_vec2 b, int color);
void	ft_mlx_batch_put(t_img *data, t_vec2 pos, t_vec2 size, int color);

int		kill_mlx(t_env *env);
int		on_keypress(int keysym, t_env *env);
void	kill_img(void *mlx, t_img *img);

void	*mlx_thread(void *arg);
int		draw_routine(t_env *env);

#endif
