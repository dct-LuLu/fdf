/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 08:27:09 by jaubry--          #+#    #+#             */
/*   Updated: 2024/11/08 15:11:01 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	Function that allocates len * size bytes using malloc.
	Protect from overflowing and sets mem allocated to 0
*/
void	*ft_calloc(size_t len, size_t size)
{
	size_t	bytes;
	void	*alloc;

	bytes = len * size;
	if (((bytes != 0) && (bytes < len || bytes < size)))
		return (NULL);
	alloc = malloc(bytes);
	if (!alloc)
		return (NULL);
	ft_memset(alloc, 0, bytes);
	return (alloc);
}

/*
#include <stdint.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int	main(void)
{
	char	*t;
	char	*tt;
	size_t	a;
	size_t	b;

	a = SIZE_MAX;
	b = SIZE_MAX;
	t = ft_calloc(a, b);
	printf("ft_calloc: %p\n", t);
	free(t);
	tt = calloc(a, b);
	printf("calloc: %p\n", tt);
	free(tt);
	return (0);
}
*/
