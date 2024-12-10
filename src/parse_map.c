/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:49:17 by jaubry--          #+#    #+#             */
/*   Updated: 2024/12/09 19:57:23 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

typedef struct s_pixel {
	int	z;
	int	color;
}	t_pixel;

typedef struct s_map {
	int	width;
	int	height;
	t_pixel	map[][];
}	t_map;
//max min? center?
//
//centrer la figure:
//trouver le point central si nombre impaire, trouver entre deux si nombre paire d'el
//une fois nombre trouve, calculer son offset par rapport a la taille de l'ecran / 2
//ajouter cet offset a tout les points dessines sur l'ecran.
/*

*/
void	read_file(int fd, t_map *map)
{
	int		height;
	char	*line;
	char	*mline;

	height = 0;
	while (!height)
	{
		line = ft_get_next_line(fd);
		if (!line)
		{
			break ;
		}
		freejoin(mline, line);
		free(line);
		height++;
	}
}

t_map	parse_map(char *file)
{
	char	***strmap;
	t_map	map;

}

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		parse_map(argv[1]);
	}
	return (0);
}

