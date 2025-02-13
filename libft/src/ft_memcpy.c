/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 07:11:56 by jaubry--          #+#    #+#             */
/*   Updated: 2024/11/14 09:34:22 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dest || src)
	{
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((const unsigned char *)src)[i];
			i++;
		}
	}
	return (dest);
}

/*
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	void	*src;

	src = malloc(1);
	printf("%p\n", memcpy(NULL, src, 0));
	printf("%p\n", ft_memcpy(NULL, src, 0));
	return (0);
}
*/
