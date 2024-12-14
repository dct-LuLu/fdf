/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 01:04:16 by jaubry--          #+#    #+#             */
/*   Updated: 2024/12/14 19:43:03 by jaubry--         ###   ########lyon.fr   */
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

typedef struct s_vec2
{
	int	x;
	int	y;
}	t_vec2;

typedef struct s_vec3
{
	int	x;
	int	y;
	int	z;
}	t_vec3;

typedef struct s_pixel
{
	int	z;
	int	color;
}	t_pixel;

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

typedef struct s_map
{
	size_t	width;
	size_t	height;
	t_vec2	offset;
	int		space;
	int		zfac;
	int		min;
	int		max;
	t_pixel	**map;
}	t_map;

typedef struct s_env
{
	void	*mlx;
	void	*win;
	t_img	img;
	t_map	map;
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
t_vec3	new_vec3(int x, int y, int z);

t_line	get_line_data(t_vec2 a, t_vec2 b);
int		argb(int a, int r, int g, int b);
t_vec2	iso(t_vec3 point);
int		abs(int x);

t_img	init_img(void *mlx, int width, int height);
void	ft_mlx_pixel_put(t_img *data, t_vec2 pos, int color);
void	ft_mlx_line_put(t_img *data, t_vec2 a, t_vec2 b, int color);
void	ft_mlx_batch_put(t_img *data, t_vec2 pos, t_vec2 size, int color);

void	draw_map(t_env env);
void	draw_segments(t_img img, t_map map, size_t x, size_t y);

t_map	init_map(char *file);
size_t	get_map_width(int fd);
size_t	get_map_height(int fd);
void	set_min_max_map(t_map *map);

t_vec3	get_point_cords(t_map map, int x, int y);
void	free_map(t_pixel **map, size_t height);

char	*format_hex(char *str);
int		hex_to_int(char *hex);

int		check_open(char *file);
void	set_space(t_map *map);
void	set_offset(t_map *map);

t_vec3	space(t_vec3 p, t_map map);
void	center(t_vec2 *p, t_map map);

int		kill(t_env *env);
int on_keypress(int keysym, t_env *env);
void	kill_img(void *mlx, t_img *img);

#endif
