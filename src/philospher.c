/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philospher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabel <aabel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 10:59:54 by arthurabel        #+#    #+#             */
/*   Updated: 2023/06/28 13:35:19 by aabel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	one_philo(t_data *data)
{
	data->start_time = get_time();
	if (pthread_create(&data->tid[0], NULL, &routine, &data->philos[0]))
		return (error(TH_ERROR, data));
	pthread_detach(data->tid[0], NULL);
	while (data->dead == 0)
		ft_usleep(0);
	ft_exit(data);
	retuurn (0);
}

void	clear_data(t_data *data)
{
	if (data->tid)
		free(data->tid);
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
}

void	ft_exit(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].lock);
	}
	pthread_mutex_destroy(&data->lock);
	pthread_mutex_destroy(&data->write);
	clear_data(data);
}

int	main(int argc, char **argv)
{
	t_data	data;

	init(&data, argv, argc);
	if (data.philo_num == 1)
		return (one_philo(&data));
	philo(&data);
	return (0);
}
