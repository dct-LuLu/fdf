/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 09:51:54 by jaubry--          #+#    #+#             */
/*   Updated: 2025/01/08 09:55:26 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stddef.h"

char	*ft_strstr(const char *big, const char *little)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!*little)
		return ((char *)big);
	while (big[i])
	{
		j = 0;
		while (little[j] && (little[j] == big[i + j]))
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

	printf("big:\t'%s'\nlittle:\t'%s'\n\n", haystack, needle);
	printf("ft_strstr\t'%s'\n", ft_strstr(haystack, needle));
	printf("strstr\t\t'%s'\n", strstr(haystack, needle));
	return (0);	
}
*/
