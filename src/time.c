/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msokolov <msokolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:10:32 by msokolov          #+#    #+#             */
/*   Updated: 2025/07/04 16:25:45 by msokolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	died(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data[i].last_meal_m);
	if (set_time() - data[i].last_meal > data->philo->die_time)
	{
		pthread_mutex_unlock(&data[i].last_meal_m);
		pthread_mutex_lock(&data->philo->died_mutex);
		data->philo->elimination = true;
		pthread_mutex_unlock(&data->philo->died_mutex);
		pthread_mutex_lock(&data->philo->print_mutex);
		printf("%lld %d has died\n",
			set_time() - data->philo->start_time, data[i].id + 1);
		pthread_mutex_unlock(&data->philo->print_mutex);
		return (false);
	}
	pthread_mutex_unlock(&data[i].last_meal_m);
	return (true);
}

long long	set_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (printf(RED"ERROR [gettimeofday]\n"RESET), 0);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
