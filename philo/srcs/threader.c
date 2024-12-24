/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threader.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 10:43:49 by snek              #+#    #+#             */
/*   Updated: 2024/12/24 11:12:25 by snek             ###   ########.fr       */
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

static int	died(int n, t_info *info, t_mutex *final)
{
	long	currenttime;
	long	ctime;
	int		i;

	i = 0;
	currenttime = gettime(0);
	ctime = gettime(1);
	while (i < n)
	{
		if (currenttime - info[i].lastmeal > (long)info->philo.die)
		{
			printf("%ldms %d died with %ld\n", ctime, i + 1,
				currenttime - info[i].lastmeal);
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
	t_info *infos, t_mutex *final)
{
	int	i;

	while (1)
	{
		if (final->num)
			break ;
		died(philo.num, infos, final);
		checkall(mutex, philo.num, philo.neats, final);
	}
	i = 0;
	while (i < philo.num)
		pthread_join(infos[i++].id, 0);
	return (free_mutex(mutex, philo.num), free(infos), 0);
}

static void	fillinfo(t_info *infos, t_philo philo, t_mutex *mutex, int i)
{
	infos->num = i + 1;
	infos->left = &mutex[i];
	if (i == philo.num -1)
		infos->right = &mutex[0];
	else
		infos->right = &mutex[i + 1];
	infos->philo = philo;
	infos->lastmeal = 0;
}

int	threader(t_philo philo, t_mutex *final, t_mutex *start)
{
	int				i;
	t_info			*infos;
	t_mutex			*mutex;

	i = 0;
	mutex = 0;
	if (init_mutex(&mutex, philo.num))
		return (1);
	infos = malloc(sizeof(t_info) * philo.num);
	if (!infos)
		return (free_mutex(mutex, philo.num), 1);
	while (i < philo.num)
	{
		fillinfo(&infos[i], philo, mutex, i);
		infos[i].final = final;
		infos[i].start = start;
		pthread_create(&infos[i].id, 0, philosopher, &infos[i]);
		i++;
	}
	while (start->num != philo.num)
		continue ;
	return (thread_observer(philo, mutex, infos, final));
}
