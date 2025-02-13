/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 06:29:25 by jaubry--          #+#    #+#             */
/*   Updated: 2024/08/21 08:24:59 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	Function that returns 1 if the character is alphanumeric else 0
*/
int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}

/*
#include <stdio.h>

int	main(void)
{
	printf("'a': %d\n", ft_isalnum('a'));
	printf("'1': %d\n", ft_isalnum('1'));
	printf("'.': %d\n", ft_isalnum('.'));
	return (0);
}
*/
