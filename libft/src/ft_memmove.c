/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 07:12:58 by jaubry--          #+#    #+#             */
/*   Updated: 2024/11/14 07:59:08 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (dest || src)
	{
		if (dest <= src)
			ft_memcpy(dest, src, n);
		else
		{
			i = 0;
			while (i < n)
			{
				((unsigned char *)dest)[n - i - 1]
					= ((const unsigned char *)src)[n - i - 1];
				i++;
			}
		}
	}
	return (dest);
}

/*
#include <string.h>
#include <stdlib.h>

int	main(void)
{
	void	*c;

	c = malloc(1);
	ft_memmove(((void*)0), ((void*)0), 5);
	return (0);
}
*/
