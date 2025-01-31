/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 01:04:16 by jaubry--          #+#    #+#             */
/*   Updated: 2025/01/29 23:13:45 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft.h"
# include <mlx.h>
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>
# ifndef WIDTH
#  define WIDTH 500
# endif
# ifndef HEIGHT
#  define HEIGHT 500
# endif
# ifndef DEBUG
#  define DEBUG 0
# endif
# include <signal.h>
# include <pthread.h>
# define MAX_SAMPLE 32768.0
extern pthread_mutex_t			stop_mutex; 
extern volatile sig_atomic_t	stop;
extern pthread_mutex_t			audio_mutex;
extern int16_t					*buffer;
extern size_t					buf_len;

typedef struct s_vec2
{
	int	x;
	int	y;
}	t_vec2;

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
	void	*mlx;
	void	*win;
	t_img	img;
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

t_vec2	new_vec2(int x, int y);

t_line	get_line_data(t_vec2 a, t_vec2 b);
int		abs(int x);
int		argb(int a, int r, int g, int b);

t_img	init_img(void *mlx, int width, int height);
void	ft_mlx_pixel_put(t_img *data, t_vec2 pos, int color);
void	ft_mlx_line_put(t_img *data, t_vec2 a, t_vec2 b, int color);
void	ft_mlx_batch_put(t_img *data, t_vec2 pos, t_vec2 size, int color);

int		kill_mlx(t_env *env);
int		on_keypress(int keysym, t_env *env);
void	kill_img(void *mlx, t_img *img);

void	*mlx_thread_feur(void *arg);

void	draw_osci(t_env env);

#endif
