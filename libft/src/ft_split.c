/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 07:20:30 by jaubry--          #+#    #+#             */
/*   Updated: 2024/12/29 21:22:14 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"

/*
	Function that counts each string there will be in the array of strings.
*/
static size_t	ft_splitlen(char const *str, char c)
{
	size_t	i;
	size_t	len;
	bool	is_in;

	i = 0;
	is_in = false;
	len = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			if (!is_in)
				len++;
			is_in = true;
		}
		else
			is_in = false;
		i++;
	}
	return (len);
}

static size_t	ft_tokenlen(char const *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			break ;
		i++;
	}
	return (i);
}

static void	ft_freesplit(char **split, size_t len)
{
	unsigned int	i;

	i = 0;
	while (i < len)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	len;
	size_t	token_len;
	char	**split;

	i = 0;
	j = 0;
	len = ft_strlen(s);
	split = ft_calloc(sizeof(char *), (ft_splitlen(s, c) + 1));
	while ((i < len) && split)
	{
		if (s[i] != c)
		{
			token_len = ft_tokenlen(s + i, c);
			split[j] = ft_strndup(s + i, token_len);
			if (!split[j])
				return (ft_freesplit(split, j), NULL);
			i += token_len;
			j++;
		}
		i++;
	}
	return (split);
}

/*
#include <unistd.h>
#include <stdio.h>

void	print_tab(char **s)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		write(1, "'", 1);
		while (s[i][j])
		{
			write(1, &s[i][j], 1);
			j++;
		}
		write(1, "'", 1);
		write(1, "\n", 1);
		free(s[i]);
		i++;
	}
	printf("'%s'\n", s[i]);
	free(s);
}

int	main(void)
{
	print_tab(ft_split("lorem ipsum dolor sit 
	amet, consectetur adipiscing elit. Sed non risus. Suspendisse", ' '));
	return (0);
}
*/
