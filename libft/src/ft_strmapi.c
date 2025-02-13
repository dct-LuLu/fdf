/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 05:35:07 by jaubry--          #+#    #+#             */
/*   Updated: 2024/11/14 09:50:24 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*r;
	size_t	i;
	size_t	len;

	if (!f)
		return (NULL);
	i = 0;
	len = ft_strlen(s);
	r = ft_calloc(sizeof(char), (len + 1));
	if (!r)
		return (NULL);
	while (i < len)
	{
		r[i] = f(i, s[i]);
		i++;
	}
	return (r);
}

/*
#include <unistd.h>

char	ft_putchar(unsigned int i, char c)
{
	(void)i;
	write(1, &c, 1);
	return (c + 1);
}

#include <stdio.h>

int	main(void)
{
	printf("\n%s\n", ft_strmapi("test abc", &ft_putchar));
	return (0);
}
*/
