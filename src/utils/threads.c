/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthurabel <arthurabel@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:40:12 by aabel             #+#    #+#             */
/*   Updated: 2023/08/02 08:39:34 by arthurabel       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

void	*monitor(void *data_pointer)
{
	t_philo	*philo;

	philo = (t_philo *) data_pointer;
	// pthread_mutex_lock(&philo->data->write);
	// printf("data val: %d\n", philo->data->dead);
	// pthread_mutex_unlock(&philo->data->write);
	while (philo->data->dead == 0)
	{
		pthread_mutex_lock(&philo->data->lock);
		if (philo->data->finished >= philo->data->philo_num)
			philo->data->dead = 1;
		pthread_mutex_unlock(&philo->data->lock);
	}
	return ((void *)0);
}

void	*supervisor(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	while (philo->data->dead == 0 && (philo->status == 0 || philo->status == 1))
	{
		pthread_mutex_lock(&philo->lock);
		if (get_time() >= philo->time_to_die && philo->data->dead == 0)//&& philo->data->dead == 0
		{
			pthread_mutex_lock(&philo->data->lock);
			messages(DIED, philo);
			philo->status = 1; //ajouter 
			pthread_mutex_unlock(&philo->data->lock);
		}
		if (philo->eat_cont == philo->data->meals_nb && philo->status == 0)
		{
			pthread_mutex_lock(&philo->data->lock);
			philo->data->finished++;
			philo->eat_cont++;
			pthread_mutex_unlock(&philo->data->lock);
		}
		if (philo->status == 1) //add
			break ;
		pthread_mutex_unlock(&philo->lock);
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
	while (philo->data->dead == 0 && philo->status == 0)
	{
		eat(philo);
		if (philo->data->meals_nb > 0)
		{
			if ((philo->eat_cont >= philo->data->meals_nb && philo->data->dead == 0))
			{
				pthread_mutex_lock(&philo->data->lock);
				philo->data->dead = 1;
				pthread_mutex_unlock(&philo->data->lock);
				break ;
			}
			if (philo->status == 1)
				break ;
		}
	}
	if (pthread_join(philo->t1, NULL))
		return ((void *)1);
	return ((void *)0);
}

int	thread_init(t_data *data)
{
	int			i;
	pthread_t	t0;

	i = -1;
	data->start_time = get_time();
	if (data->meals_nb > 0)
	{
		if (pthread_create(&t0, NULL, &monitor, &data->philos[0]))
			return (error(TH_ERROR, data));
	}
	while (++i < data->philo_num)
	{
		pthread_mutex_lock(&data->lock);
		if (pthread_create(&data->tid[i], NULL, &routine, &data->philos[i]))
			return (error(TH_ERROR, data));
		pthread_mutex_unlock(&data->lock);
		ft_usleep(1);
	}
	i = -1;
	while (++i < data->philo_num)
	{
		if (pthread_join(data->tid[i], NULL))
			return (error(JOIN_ERR, data));
	}
	return (0);
}
