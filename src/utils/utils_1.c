/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabel <aabel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 16:15:45 by aabel             #+#    #+#             */
/*   Updated: 2023/08/09 16:23:28 by aabel            ###   ########.fr       */
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
