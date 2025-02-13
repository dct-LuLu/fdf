/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:34:00 by jaubry--          #+#    #+#             */
/*   Updated: 2024/11/14 07:42:57 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	if (alst && *alst)
		ft_lstadd_back(&((*alst)->next), new);
	else if (!alst)
		alst = &new;
	else
		*alst = new;
}

/*
#include <stdio.h>

void	ft_lstprint(t_list *lst)
{
	t_list	*next;

	next = lst;
	while (next)
	{
		printf("[%s]-> ", (char *)next->content);
		next = next->next;
	}
	printf("[NULL]");
}

int	main(void)
{
	t_list	*lst;

	lst = ft_lstnew("1");
	ft_lstadd_back(&lst, ft_lstnew("2"));
	ft_lstadd_back(&lst, ft_lstnew("3"));
	ft_lstprint(lst);
	return (0);
}
*/
