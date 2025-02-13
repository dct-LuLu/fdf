/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:36:13 by jaubry--          #+#    #+#             */
/*   Updated: 2024/11/14 07:56:34 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first;
	t_list	*node;
	void	*tmp;

	first = NULL;
	while (lst && f && del)
	{
		tmp = f(lst->content);
		if (!tmp)
		{
			ft_lstclear(&first, del);
			return (NULL);
		}
		node = ft_lstnew(tmp);
		if (!node)
		{
			del(tmp);
			ft_lstclear(&first, del);
			return (NULL);
		}
		ft_lstadd_back(&first, node);
		lst = lst->next;
	}
	return (first);
}

/*
#include <stdio.h>

void	*__ft_strlen(void *str)
{
	size_t	i;

	i = 0;
	while (((char *)str)[i])
		i++;
	return ((void *)i);
}

void	show(void *content)
{
	printf("%s\n", (char *)content);
}

void	show2(void *content)
{
	printf("%d\n", (int)content);
}

void	feur(void *content)
{
	(void)content;
}

int	main(void)
{
	t_list	*lst;
	t_list	*new;

	lst = ft_lstnew("ceci");
	ft_lstiter(lst, &show);
	printf("\n");
	new = ft_lstmap(lst, &__ft_strlen, &free);
	ft_lstiter(new, &show2);
	//ft_lstdelone(lst, &free);
	//free(lst->content);
	free(lst);
	ft_lstclear(&new, &feur);
	return (0);
}
*/
