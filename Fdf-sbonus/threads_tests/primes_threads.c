/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:26:33 by jaubry--          #+#    #+#             */
/*   Updated: 2025/01/29 13:44:44 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>

void	*routine(void *nb)
{
	printf("%d\n", *(int *)nb);
	return (NULL);
}

int	main(void)
{
	pthread_t	th[10];
	int			arr[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
	int			i;

	i = 0;
	while (i < 10)
	{
		if (pthread_create(th + i, NULL, &routine, arr + i) != 0)
			perror("Failed to create thread");
		i++;
	}
	i = 0;
	while (i < 10)
	{
		if (pthread_join(th[i], NULL) != 0)
			perror("Failed to join thread");
		i++;
	}
	return (0);
}
