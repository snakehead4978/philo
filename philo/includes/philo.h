/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:02:44 by snek              #+#    #+#             */
/*   Updated: 2024/12/24 11:13:51 by snek             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

enum
{
	EAT,
	SLEEP,
	THINK,
	FORK
};

typedef struct s_philo
{
	int	num;
	int	die;
	int	sleep;
	int	eats;
	int	neats;
}		t_philo;

typedef struct s_mutex
{
	pthread_mutex_t	id;
	int				num;
}		t_mutex;

typedef struct s_info
{
	t_philo			philo;
	pthread_t		id;
	int				num;
	t_mutex			*left;
	t_mutex			*right;
	t_mutex			*final;
	long			lastmeal;
	t_mutex			*start;
}		t_info;

long	gettime(int mode);
int		printer(int num, int action, t_mutex *death);
void	*philosopher(void *info);
int		init_mutex(t_mutex **mutex, int n);
void	free_mutex(t_mutex *mutex, int n);
int		threader(t_philo philo, t_mutex *final, t_mutex *start);

#endif