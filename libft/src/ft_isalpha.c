/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 06:22:12 by jaubry--          #+#    #+#             */
/*   Updated: 2024/08/21 06:00:30 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Function that returns 1 if the character is in the alphabet else 0
*/
int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/*
#include <stdio.h>

int	main(void)
{
	printf("'a': %d\n", ft_isalpha('a'));
	printf("'.': %d\n", ft_isalpha('.'));
	return (0);
}
*/
