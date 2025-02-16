/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 02:04:52 by jaubry--          #+#    #+#             */
/*   Updated: 2025/02/16 21:41:27 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	Returns the number of "tokens" separated by the char sep
*/
int	count_tokens(const char *str, char sep)
{
	size_t	i;
	int		count;
	bool	in;

	i = 0;
	count = 0;
	in = false;
	while (str && str[i] && str[i] != '\n')
	{
		if (!in && (str[i] != sep))
		{
			in = true;
			count++;
		}
		else if (str[i] == sep)
			in = false;
		i++;
	}
	return (count);
}
