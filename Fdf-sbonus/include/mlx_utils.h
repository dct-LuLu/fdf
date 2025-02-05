/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 01:04:16 by jaubry--          #+#    #+#             */
/*   Updated: 2025/02/05 20:01:10 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_UTILS_H
# define MLX_UTILS_H
# include "vec2.h"
# include "color.h"
# include "audio_utils.h"
# include <stdlib.h>
# include <stdbool.h>
# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>
# ifndef WIDTH
#  define WIDTH 1000
# endif
# ifndef HEIGHT
#  define HEIGHT 1000
# endif

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
	//t_pa	*pa;
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

t_env	setup_mlx();
int	kill_mlx(t_env *env);
int		mlx_hook_n_loop(t_env env);

int		on_keypress(int keysym, t_env *env);

void	ft_mlx_line_put(t_img *img, t_vec2 a, t_vec2 b, int color);
void	ft_mlx_pixel_put(t_img *img, t_vec2 pos, int color);

t_img	init_img(void *mlx, int width, int height);
void	kill_img(void *mlx, t_img *img);

int		argb(int a, int r, int g, int b);

/*
t_img	init_img(void *mlx, int width, int height);
void	ft_mlx_pixel_put(t_img *data, t_vec2 pos, int color);
//void	ft_mlx_line_put(t_img *data, t_vec2 a, t_vec2 b, int color);
//void	ft_mlx_batch_put(t_img *data, t_vec2 pos, t_vec2 size, int color);


char	*format_hex(char *str);
int		hex_to_int(char *hex);

//int		check_open(char *file);

int		kill(t_env *env);
int		mouse_handler(int mousecode, int x, int y, t_env *env);
int		on_keypress(int keysym, t_env *env);
void	kill_img(void *mlx, t_img *img);
*/

#endif //MLX_UTILS_H
