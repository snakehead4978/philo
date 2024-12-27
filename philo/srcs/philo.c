/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 10:29:05 by snek              #+#    #+#             */
/*   Updated: 2024/12/27 01:02:42 by snek             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	eat(t_info *infos)
{
	pthread_mutex_lock(&infos->left->id);
	printer(infos->num, FORK, infos->final);
	if (infos->left == infos->right)
	{
		pthread_mutex_unlock(&infos->left->id);
		usleep((infos->philo.die * 2000));
		return (1);
	}
	pthread_mutex_lock(&infos->right->id);
	printer(infos->num, FORK, infos->final);
	pthread_mutex_lock(&infos->lastmeal->id);
	infos->lastmeal->num = gettime(0);
	pthread_mutex_unlock(&infos->lastmeal->id);
	infos->left->num++;
	printer(infos->num, EAT, infos->final);
	usleep(infos->philo.eats * 1000);
	pthread_mutex_unlock(&infos->left->id);
	pthread_mutex_unlock(&infos->right->id);
	return (0);
}

int	checkmutex(t_mutex *mutex, int num)
{
	int	i;

	i = 1;
	pthread_mutex_lock(&mutex->id);
	if (mutex->num == num)
		i = 0;
	pthread_mutex_unlock(&mutex->id);
	return (i);
}

static void	philo_starter(t_info *infos)
{
	pthread_mutex_lock(&infos->start->id);
	infos->start->num++;
	pthread_mutex_unlock(&infos->start->id);
	while (checkmutex(infos->start, infos->philo.num))
		usleep(10);
	pthread_mutex_lock(&infos->lastmeal->id);
	infos->lastmeal->num = gettime(0);
	pthread_mutex_unlock(&infos->lastmeal->id);
	if (infos->num % 2 -1)
		usleep(infos->philo.eats * 500);
}

void	*philosopher(void *info)
{
	t_info	*infos;

	infos = info;
	philo_starter(infos);
	while (checkmutex(infos->final, 1))
	{
		eat(infos);
		printer(infos->num, SLEEP, infos->final);
		usleep(infos->philo.sleep * 1000);
		printer(infos->num, THINK, infos->final);
	}
	return (0);
}
