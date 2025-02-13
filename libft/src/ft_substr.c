/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 06:19:20 by jaubry--          #+#    #+#             */
/*   Updated: 2024/11/14 10:22:28 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_len;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	s_len = ft_strlen(s);
	if (start >= s_len)
		substr = ft_calloc(sizeof(char), 1);
	else if (start + len > s_len)
		substr = ft_calloc(sizeof(char), (ft_strlen(s + start) + 1));
	else
		substr = ft_calloc(sizeof(char), (len + 1));
	if (!substr)
		return (NULL);
	while ((i < len) && (start < s_len) && s[start + i])
	{
		substr[i] = s[start + i];
		i++;
	}
	return (substr);
}

/*
#include <stdio.h>

int	main(void)
{
	char *str = "i just want this part #############";
	size_t size = 10;

	printf("'%s'\n", ft_substr(str, 5, size));
	return (0);
}
*/
