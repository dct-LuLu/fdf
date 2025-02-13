/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 07:58:07 by jaubry--          #+#    #+#             */
/*   Updated: 2024/11/14 09:59:22 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stddef.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!*little)
		return ((char *)big);
	while (big[i] && (i < len))
	{
		j = 0;
		while (little[j] && (little[j] == big[i + j]) && (i + j < len))
		{
			j++;
			if (!little[j])
				return ((char *)(big + i));
		}
		i++;
	}
	return (NULL);
}

/*
#include <stdio.h>
#include <bsd/string.h>

int	main(void)
{
	char	*haystack = "abcdefgh";//"teste";
	char	*needle = "abc";
	char	n = 2;

	printf("big:\t'%s'\nlittle:\t'%s'\nn:\t%d\n\n", haystack, needle, n);
	printf("ft_strnstr\t'%s'\n", ft_strnstr(haystack, needle, n));
	printf("strnstr\t\t'%s'\n", strnstr(haystack, needle, n));
	return (0);	
}
*/
