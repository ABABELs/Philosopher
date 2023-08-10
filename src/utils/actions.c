/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabel <aabel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:07:56 by aabel             #+#    #+#             */
/*   Updated: 2023/08/10 14:27:31 by aabel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

void	eat(t_philo *philo)
{
	take_forks(philo);
	philo->time_to_die = philo->data->death_time + get_time();
	philo->eating = 1;
	messages(EATING, philo);
	ft_usleep(philo->data->eat_time);
	philo->eating = 0;
	philo->eat_cont++;
	drop_forks(philo);
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		messages(TAKE_FORKS, philo);
		pthread_mutex_lock(philo->r_fork);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		messages(TAKE_FORKS, philo);
		pthread_mutex_lock(philo->l_fork);
	}
	messages(TAKE_FORKS, philo);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	messages(SLEEPING, philo);
	ft_usleep(philo->data->sleep_time);
	messages(THINKING, philo);
}

void	messages(char *str, t_philo *philo)
{
	u_int64_t	time;

	pthread_mutex_lock(&philo->data->write);
	time = get_time() - philo->data->start_time;
	if ((ft_strcmp(DIED, str) == 0 && philo->eating == 0))
	{
		printf("%llu %d %s\n", time, philo->id, str);
		pthread_mutex_lock(&philo->data->lock);
		philo->data->dead = 1;
		pthread_mutex_unlock(&philo->data->lock);
	}
	else if (!philo->data->dead)
		printf("%llu %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->write);
}

u_int64_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (error("gettimeofday() FAILURE\n", NULL));
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}
