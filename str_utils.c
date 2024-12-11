/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:03:34 by jaubry--          #+#    #+#             */
/*   Updated: 2024/12/11 22:35:24 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
	Removes the 0x and toupper the hex string.
*/
char	*format_hex(char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (str[i] && str[i] == '0')
		i++;
	if (str[i] && str[i] == 'x')
		i++;
	j = 0;
	while (str[i + j])
	{
		ft_toupper(str[i + j]);
		j++;
	}
	return (str + i);
}

/*
	Transform a formated hex string to an int.
*/
int	hex_to_int(char *hex)
{
	size_t	i;
	size_t	len;
	int		num;

	len = ft_strlen(hex);
	i = 0;
	num = 0;
	while (hex[i])
	{
		if ((hex[i] >= 'A') && (hex[i] <= 'F'))
			num += (hex[i] - 55) * pow(16, len - i - 1);
		else if ((hex[i] >= '0') && (hex[i] <= '9'))
			num += (hex[i] - 48) * pow(16, len - i - 1);
		i++;
	}
	return (num);
}

/*
int	main(void)
{
	char	*str = "0x458FF";

	printf("%s = %d\n", str, hex_to_int(format_hex(str)));
}
*/
