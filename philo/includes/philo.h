/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:02:44 by snek              #+#    #+#             */
/*   Updated: 2024/12/27 03:17:58 by snek             ###   ########.fr       */
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

typedef struct s_mealmutex
{
	pthread_mutex_t	id;
	long			num;
}		t_mealmutex;

typedef struct s_info
{
	t_philo			philo;
	pthread_t		id;
	int				num;
	t_mutex			*left;
	t_mutex			*right;
	t_mutex			*final;
	t_mealmutex		*lastmeal;
	t_mutex			*start;
}		t_info;

long	gettime(int mode);
int		printer(int num, int action, t_mutex *death);
void	*philosopher(void *info);
int		init_mutex(t_mutex **mutex, int n);
void	free_mutex(t_mutex *mutex, t_mealmutex *meals, int n);
int		threader(t_philo philo, t_mutex *final, t_mutex *start, int i);
int		ft_atoi(const char *nptr);
int		checkmutex(t_mutex *mutex, int num);
int		init_mealmutex(t_mealmutex **mutex, int n);
void	fillinfo(t_info *infos, t_philo philo, t_mutex *mutex, int i);

#endif