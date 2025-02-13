/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 07:09:13 by jaubry--          #+#    #+#             */
/*   Updated: 2024/11/14 07:31:21 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

/*
int	main(void)
{
	void	*p;
	void	*ps;
	int		t;

	t = 4;
	p = &t;
	ps = NULL;
	ft_bzero(p, 5);
	ft_bzero(ps, 5);
	

	return (0);
}
*/
