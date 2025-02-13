/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:09:17 by jaubry--          #+#    #+#             */
/*   Updated: 2025/02/11 16:58:34 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_UTILS_H
# define MLX_UTILS_H
//# include "mlx.h"
# include "libft.h"
# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "vec2.h"
# include "rainbow.h"

# ifndef WIDTH
#  define WIDTH 500
# endif
# ifndef HEIGHT
#  define HEIGHT 500
# endif
# ifndef RAINBOW
#  define RAINBOW 0
# endif
# ifndef HUE_SPEED
#  define HUE_SPEED 1
# endif

# define BACKGROUND 0x0F000000
# define DOT 0x0000FF19 //GREEN BLUEISH
//# define COLOR 0x00A92299 //PINK

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

typedef struct s_mlx
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
	int				ret;
}	t_mlx;

typedef struct s_line
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;
}	t_line;

int		abs(int x);

t_img	init_img(void *mlx, int width, int height);
void	ft_mlx_pixel_put(t_img *data, t_vec2 pos, int color);
void	ft_mlx_line_put(t_img *data, t_vec2 a, t_vec2 b, int color);
void	ft_mlx_batch_put(t_img *data, t_vec2 pos, t_vec2 size, int color);

int		kill_mlx(t_mlx *mlx);
int		on_keypress(int keysym, t_mlx *mlx);
void	kill_img(void *mlx, t_img *img);

#endif // MLX_UTILS_H
