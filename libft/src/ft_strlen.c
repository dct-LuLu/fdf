/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 06:58:40 by jaubry--          #+#    #+#             */
/*   Updated: 2024/11/05 17:02:43 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/*
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int	main(void)
{
	//printf("len of 'NULL': %ld\n", strlen(NULL));
	printf("len of 'test': %ld\n", ft_strlen("test"));
	printf("len of 'NULL': %ld\n", ft_strlen(NULL));
	return (0);
}
*/

/*
	Protect with NULL value?
*/
