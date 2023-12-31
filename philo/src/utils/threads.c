/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabel <aabel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:40:12 by aabel             #+#    #+#             */
/*   Updated: 2023/08/11 12:41:46 by aabel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

void	*supervisor(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	while (philo->data->dead == 0)
	{
		if (get_time() > philo->time_to_die && philo->data->dead == 0)
		{
			messages(DIED, philo);
		}
		if (philo->eat_cont >= philo->data->meals_nb
			&& philo->data->dead == 0 && philo->data->meals_nb > 0)
		{
			pthread_mutex_lock(&philo->data->lock);
			philo->eat_cont++;
			pthread_mutex_unlock(&philo->data->lock);
			break ;
		}
	}
	return ((void *)0);
}

void	*routine(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	philo->time_to_die = philo->data->death_time + get_time();
	if (pthread_create(&philo->t1, NULL, &supervisor, (void *)philo))
		return ((void *)1);
	while (philo->data->dead == 0)
	{
		eat(philo);
		pthread_mutex_lock(&philo->lock);
		if (philo->data->meals_nb > 0)
		{
			if (check_all_fill_eat(philo))
				break ;
			if (philo->eat_cont >= philo->data->meals_nb)
				break ;
		}
		pthread_mutex_unlock(&philo->lock);
	}
	if (pthread_join(philo->t1, NULL))
		return ((void *)1);
	return ((void *)0);
}

int	thread_init(t_data *data)
{
	int			i;
	pthread_t	t0;

	i = 0;
	data->start_time = get_time();
	philo_start(data);
	i = -1;
	while (++i < data->philo_num)
	{
		if (pthread_join(data->tid[i], NULL))
			return (error(JOIN_ERR, data));
	}
	return (0);
}

int	philo_start(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_create(&data->tid[i], NULL, &routine, &data->philos[i]))
			return (error(TH_ERROR, data));
		i += 2;
	}
	i = 1;
	while (i < data->philo_num)
	{
		if (pthread_create(&data->tid[i], NULL, &routine, &data->philos[i]))
			return (error(TH_ERROR, data));
		i += 2;
	}
	return (0);
}
