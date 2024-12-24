/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 10:29:05 by snek              #+#    #+#             */
/*   Updated: 2024/12/24 10:42:47 by snek             ###   ########.fr       */
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
	infos->lastmeal = gettime(0);
	infos->left->num++;
	printer(infos->num, EAT, infos->final);
	usleep(infos->philo.eats * 1000);
	pthread_mutex_unlock(&infos->left->id);
	pthread_mutex_unlock(&infos->right->id);
	return (0);
}

static void	philo_starter(t_info *infos)
{
	pthread_mutex_lock(&infos->start->id);
	if (infos->start->num +1 == infos->philo.num)
		gettime(2);
	infos->start->num++;
	pthread_mutex_unlock(&infos->start->id);
	while (infos->start->num != infos->philo.num)
		continue ;
	infos->lastmeal = gettime(0);
	if (infos->num % 2 -1)
		usleep(infos->philo.eats * 500);
}

void	*philosopher(void *info)
{
	t_info	*infos;

	infos = info;
	philo_starter(infos);
	while (!infos->final->num)
	{
		eat(infos);
		printer(infos->num, SLEEP, infos->final);
		usleep(infos->philo.sleep * 1000);
		printer(infos->num, THINK, infos->final);
	}
	return (0);
}
