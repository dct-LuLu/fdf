/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 01:04:16 by jaubry--          #+#    #+#             */
/*   Updated: 2024/12/03 01:40:04 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

typedef struct s_data {
	void	*img;
	char	*addr;
	int		byte_depth;
	int		line_len;
	int		endian;
}	t_data;

typedef struct s_vec2 {
	int	x;
	int	y;
}	t_vec2;

typedef struct s_vec3 {
	int	x;
	int	y;
	int	z;
}	t_vec3;

void	ft_mlx_batch_put(t_data *data, t_vec2 pos, t_vec2 size, int color);

void	ft_mlx_pixel_put(t_data *data, t_vec2 pos, int color);

void	ft_mlx_line_put(t_data *data, t_vec2 a, t_vec2 b, int color);

int	argb(int a, int r, int g, int b);

t_vec2	new_vec2(int x, int y);

#endif
