
#include "fdf.h"

int	kill(t_env *env)
{
	free_map(env->map.map, env->map.height);
	mlx_destroy_image(env->mlx, env->img.img);
	mlx_destroy_window(env->mlx, env->win);
	mlx_destroy_display(env->mlx);
	exit(0);
	return (0);
}