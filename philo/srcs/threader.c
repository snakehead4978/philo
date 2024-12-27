/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threader.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 10:43:49 by snek              #+#    #+#             */
/*   Updated: 2024/12/27 01:03:57 by snek             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	checkall(t_mutex *mutex, int n, int num, t_mutex *final)
{
	int	i;

	if (num <= -1)
		return (1);
	i = 0;
	while (i < n)
	{
		if (mutex[i].num < num)
			return (0);
		i++;
	}
	pthread_mutex_lock(&final->id);
	final->num = 1;
	pthread_mutex_unlock(&final->id);
	printf("All philos have eaten %d times.\n", num);
	return (1);
}

static long	getmeal(t_info mutex)
{
	long	i;

	pthread_mutex_lock(&mutex.lastmeal->id);
	i = mutex.lastmeal->num;
	pthread_mutex_unlock(&mutex.lastmeal->id);
	return (i);
}

static int	died(int n, t_info *info, t_mutex *final)
{
	long	currenttime;
	long	ctime;
	int		i;
	long	c;

	i = 0;
	currenttime = gettime(0);
	ctime = gettime(1);
	while (i < n)
	{
		c = getmeal(info[i]);
		if (currenttime - c > (long)info->philo.die)
		{
			printf("%ldms %d died\n", ctime, i + 1);
			pthread_mutex_lock(&final->id);
			final->num = 1;
			pthread_mutex_unlock(&final->id);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	thread_observer(t_philo philo, t_mutex *mutex,
	t_info *infos, t_mealmutex *meals)
{
	int	i;

	usleep(100);
	while (1)
	{
		if (infos[0].final->num)
			break ;
		died(philo.num, infos, infos[0].final);
		checkall(mutex, philo.num, philo.neats, infos[0].final);
	}
	i = 0;
	while (i < philo.num)
		pthread_join(infos[i++].id, 0);
	return (free_mutex(mutex, meals, philo.num), free(infos), 0);
}

int	threader(t_philo philo, t_mutex *final, t_mutex *start, int i)
{
	t_info			*infos;
	t_mutex			*mutex;
	t_mealmutex		*meals;

	mutex = 0;
	meals = 0;
	if (init_mutex(&mutex, philo.num) || init_mealmutex(&meals, philo.num))
		return (free(mutex), 1);
	infos = malloc(sizeof(t_info) * philo.num);
	if (!infos)
		return (free_mutex(mutex, meals, philo.num), 1);
	while (++i < philo.num)
	{
		if (i + 1 == philo.num)
			gettime(2);
		fillinfo(&infos[i], philo, mutex, i);
		infos[i].lastmeal = &meals[i];
		infos[i].final = final;
		infos[i].start = start;
		pthread_create(&infos[i].id, 0, philosopher, &infos[i]);
	}
	while (checkmutex(start, philo.num))
		usleep(10);
	return (thread_observer(philo, mutex, infos, meals));
}
