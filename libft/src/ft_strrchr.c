/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 07:33:52 by jaubry--          #+#    #+#             */
/*   Updated: 2024/11/14 10:09:03 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	i = 0;
	while (i < len)
	{
		if (s[len - i - 1] == (char)c)
			return ((char *)(s + (len - 1 - i)));
		i++;
	}
	if ((char)c == '\0')
		return ((char *)(s + len));
	return (NULL);
}

/*
#include <stdio.h>
int	main(void)
{
	printf("'%s'\n", ft_strrchr("", '\0'));
	return (0);
}
*/
/*
	//Old implementation
char	*strrchr(const char *s, int c)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(s);
	if (!c)
		return ((char *)(&s[len]));
	while (i <= len)
	{
		if (s[len - i - 1] == (char)c)
			return ((char *)(&s[len - i - 1]));
		i++;
	}
	return (NULL);
}
*/
/*
#include <stdio.h>

int	main(void)
{
	//printf("%d\n", (char)(1024 + 'e'));
	printf("\n%s", ft_strrchr("teste", 1024));
	return (0);
}
*/
