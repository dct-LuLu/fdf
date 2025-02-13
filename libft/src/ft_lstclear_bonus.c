/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:35:03 by jaubry--          #+#    #+#             */
/*   Updated: 2024/11/14 07:51:42 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (lst && del)
	{
		while (*lst)
		{
			tmp = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = tmp;
		}
		*lst = NULL;
	}
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
	printf("[NULL]\n");
}

void	rem(void *el)
{
	free(el);
}

int	main(void)
{
	t_list	*lst;
	char	*t1;
	char	*t2;
	char	*t3;

	t1 = malloc(sizeof(char) * 2);
	t2 = malloc(sizeof(char) * 2);
	t3 = malloc(sizeof(char) * 2);
	t1[0] = '1';
	t2[0] = '2';
	t3[0] = '3';
	t1[1] = '\0';
	t2[1] = '\0';
	t3[1] = '\0';

	lst = ft_lstnew(t1);
	ft_lstadd_back(&lst, ft_lstnew(t2));
	ft_lstadd_back(&lst, ft_lstnew(t3));
	ft_lstprint(lst);
	ft_lstclear(&(lst), &rem);
	//ft_lstprint(lst);
	return (0);
}
*/
