/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithreaded_sum.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:48:39 by jaubry--          #+#    #+#             */
/*   Updated: 2025/01/29 14:55:36 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_sum
{
	int	len;
	int	*arr;
}	t_sum;

void	*fsum(void *arg)
{
	int	i;
	int	*sum;
	t_sum	*s;

	s = (t_sum *) (arg);
	i = 0;
	sum = malloc(sizeof(int));
	*sum = 0;
	printf("accessing values: [ ");
	while (i < s->len)
	{
		printf("%d ", s->arr[i]);
		*sum += s->arr[i];
		i++;
	}
	printf("]\n");
	printf("sum:%d\n", *sum);
	return ((void *)sum);
}

void	split_sum(pthread_t *th, int *arr)
{
	t_sum	*s;

	s = calloc(1, sizeof(t_sum));
	s->len = 5;
	s->arr = arr;
	printf("first val %d\n", arr[0]);
	if (pthread_create(th, NULL, fsum, s) != 0)
		perror("Error while creating pthread");
}

int	main(void)
{
	int	arr[10] = {5, 1, -5, 45, 1 , 2, 4, 8, 10, 9};
	pthread_t	th1, th2;
	int	total;
	int	*res1, *res2;

	split_sum(&th1, arr);
	split_sum(&th2, arr + 5);

	pthread_join(th1, (void **)&res1);
	pthread_join(th2, (void **)&res2);
	total = *res1 + *res2;
	printf("total: %d\n", total);
	free(res1);
	free(res2);
	return (0);
}
