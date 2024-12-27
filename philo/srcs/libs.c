/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 17:41:27 by snek              #+#    #+#             */
/*   Updated: 2024/12/26 21:45:23 by snek             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int			i;
	long		sign;
	long		res;

	sign = 1;
	i = 0;
	res = 0;
	while (nptr[i] == 32 || (nptr[i] <= 13 && nptr[i] >= 9))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
		res = res * 10 + nptr[i++] - '0';
	return ((int)(res * sign));
}

void	fillinfo(t_info *infos, t_philo philo, t_mutex *mutex, int i)
{
	infos->num = i + 1;
	infos->left = &mutex[i];
	if (i == philo.num -1)
		infos->right = &mutex[0];
	else
		infos->right = &mutex[i + 1];
	infos->philo = philo;
}
