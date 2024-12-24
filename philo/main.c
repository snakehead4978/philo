/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:10:50 by snek              #+#    #+#             */
/*   Updated: 2024/12/24 11:10:55 by snek             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	checknum(char *num, int *err)
{
	int	n;

	n = ft_atoi(num);
	if (n < 0)
		printf("Error: %d : Positive numbers only\n", n);
	else if (n > 100000)
		printf("Error: %d : Number too big, will take too long\n", n);
	if (n < 0 || n > 100000)
		*err = 0;
	return (n);
}

static int	init_philo(int ac, char **av, t_philo *philo)
{
	int	err;

	err = 1;
	philo->num = checknum(av[1], &err);
	philo->die = checknum(av[2], &err);
	philo->eats = checknum(av[3], &err);
	philo->sleep = checknum(av[4], &err);
	philo->neats = -1;
	if (ac == 6)
		philo->neats = checknum(av[5], &err);
	if (!err)
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_philo	philo;
	t_mutex	*final;
	t_mutex	*start;

	if (ac < 5 || ac > 6)
		return (1);
	if (init_philo(ac, av, &philo))
		return (1);
	final = malloc(sizeof(t_mutex));
	if (!final)
		return (1);
	start = malloc(sizeof(t_mutex));
	if (!start)
		return (free(final), 1);
	final->num = 0;
	pthread_mutex_init(&final->id, 0);
	threader(philo, final, start);
	return (free(final), free(start), 0);
}
