/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 01:04:16 by jaubry--          #+#    #+#             */
/*   Updated: 2024/12/11 15:48:30 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft.h"
# include <math.h>

typedef struct s_img {
	void	*img;
	char	*addr;
	int		byte_depth;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_vec2 {
	int	x;
	int	y;
}	t_vec2;

typedef struct s_vec3 {
	int	x;
	int	y;
	int	z;
}	t_vec3;

typedef struct s_pixel {
	int	z;
	int	color;
}	t_pixel;

void	ft_mlx_batch_put(t_img *data, t_vec2 pos, t_vec2 size, int color);

void	ft_mlx_pixel_put(t_img *data, t_vec2 pos, int color);

void	ft_mlx_line_put(t_img *data, t_vec2 a, t_vec2 b, int color);

int	argb(int a, int r, int g, int b);

t_vec2	new_vec2(int x, int y);

t_vec3	new_vec3(int x, int y, int z);

typedef struct s_map {
	size_t	width;
	size_t	height;
	t_vec2	offset;
	int		fact;
	t_pixel	**map;
}	t_map;

typedef struct s_env {
	void	*mlx;
	void	*win;
	t_img	img;
	t_map	map;
}	t_env;

size_t	get_map_width(int fd);

size_t	get_map_height(int fd);

void	free_map(t_pixel **map, size_t height);

t_map	init_map(char *file);

int	check_open(char *file);

char	*format_hex(char *str);

int	hex_to_int(char *hex);


void	set_fact(t_map *map, t_img img);

void	set_offset(t_map *map, t_img img);

t_vec2	iso(t_vec3 point);

#endif
