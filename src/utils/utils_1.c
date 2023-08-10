/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabel <aabel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 16:15:45 by aabel             #+#    #+#             */
/*   Updated: 2023/08/10 12:32:52 by aabel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

int	check_in(t_data *data)
{
	if (data->philo_num > INT32_MAX)
		return (1);
	else if (data->death_time > INT32_MAX)
		return (1);
	else if (data->eat_time > INT32_MAX)
		return (1);
	else if (data->sleep_time > INT32_MAX)
		return (1);
	else if (data->meals_nb > INT32_MAX)
		return (1);
	else
		return (0);
}


int	check_all_fill_eat(t_philo *philo)
{
	int	i;
	int	u;

	i = 0;
	u = 0;
	while (i < philo->data->philo_num)
	{
		if (philo->data->philos[i].eat_cont >= philo->data->meals_nb)
			u++;
		i++;
	}
	if (u == philo->data->philo_num)
	{
		pthread_mutex_lock(&philo->data->lock);
		philo->data->dead = 1;
		pthread_mutex_unlock(&philo->data->lock);
		return (1);
	}
	else
		return (0);
}
