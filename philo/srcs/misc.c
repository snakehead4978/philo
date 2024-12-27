/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 20:05:36 by snek              #+#    #+#             */
/*   Updated: 2024/12/26 21:43:53 by snek             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static void	printlong(long num1, int num2)
// {
// 	ft_putnbr(num1);
// 	write(1, "ms ", 3);
// 	ft_putnbr(num2);
// }

int	printer(int num, int action, t_mutex *death)
{
	pthread_mutex_lock(&death->id);
	if (death->num)
		return (pthread_mutex_unlock(&death->id));
	if (action == EAT)
		printf("%ldms %d is eating\n", gettime(1), num);
	else if (action == SLEEP)
		printf("%ldms %d is sleeping\n", gettime(1), num);
	else if (action == THINK)
		printf("%ldms %d is thinking\n", gettime(1), num);
	else
		printf("%ldms %d has taken a fork\n", gettime(1), num);
	return (pthread_mutex_unlock(&death->id));
}

long	gettime(int mode)
{
	static long		realtime;
	struct timeval	time;

	gettimeofday(&time, 0);
	if (mode == 2)
	{
		realtime = time.tv_sec * 1000 + time.tv_usec / 1000;
		return (0);
	}
	if (!mode)
		return (time.tv_sec * 1000 + time.tv_usec / 1000);
	return (time.tv_sec * 1000 + time.tv_usec / 1000 - realtime);
}

int	init_mutex(t_mutex **mutex, int n)
{
	int	i;
	int	err;

	i = 0;
	*mutex = malloc(sizeof(t_mutex) * n);
	if (!*mutex)
		return (1);
	err = 0;
	while (i < n && !err)
	{
		(*mutex)[i].num = 0;
		err = pthread_mutex_init(&(*mutex)[i].id, 0);
		i++;
	}
	if (err)
	{
		i -= 2;
		while (i >= 0)
			pthread_mutex_destroy(&(*mutex)[i--].id);
		return (free(*mutex), 1);
	}
	return (0);
}

int	init_mealmutex(t_mealmutex **mutex, int n)
{
	int	i;
	int	err;

	i = 0;
	*mutex = malloc(sizeof(t_mealmutex) * n);
	if (!*mutex)
		return (1);
	err = 0;
	while (i < n && !err)
	{
		(*mutex)[i].num = 0;
		err = pthread_mutex_init(&(*mutex)[i].id, 0);
		i++;
	}
	if (err)
	{
		i -= 2;
		while (i >= 0)
			pthread_mutex_destroy(&(*mutex)[i--].id);
		return (free(*mutex), 1);
	}
	return (0);
}

void	free_mutex(t_mutex *mutex, t_mealmutex *meals, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&mutex[i].id);
		pthread_mutex_destroy(&meals[i++].id);
	}
	free(mutex);
	free(meals);
}
