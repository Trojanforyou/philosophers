/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msokolov <msokolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:04:14 by msokolov          #+#    #+#             */
/*   Updated: 2025/06/26 18:38:00 by msokolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitoring(void *args)
{
	t_data	*data;
	data = (t_data *)args;
	int	i;
	while (1)
	{
		i = -1;
		while (++i < data->philo->philo_nbr)
		{
			pthread_mutex_lock(&data[i].last_meal_m);
			if (set_time() - data[i].last_meal > data->philo->die_time)
			{
				pthread_mutex_unlock(&data[i].last_meal_m);
				pthread_mutex_lock(&data->philo->died_mutex);
				data->philo->elimination = true;
				pthread_mutex_unlock(&data->philo->died_mutex);
				printf("%lld %s", set_time() - data->philo->start_time, "has died\n");
				return (0);
			}
			else
				pthread_mutex_unlock(&data[i].last_meal_m);
		}
		usleep(1000);
	}
	return (0);
}
// Основной цикл рутины.
void	*routine(void *args)
{
	t_data *data;
	data = (t_data *)args;
	usleep((data->id % 2) * (data->philo->eat_time * 100));
	while (is_simulation_running(data))
	{
		print_msg(data,"is thinking\n");
		if (data->philo->philo_nbr % 2 == 1)
			usleep(1500);
		deadlock_case(data);
		print_msg(data,"is eating\n");
		usleep(data->philo->eat_time * 1000);
		data->meals_eaten++;
		pthread_mutex_unlock(data->left_fork);
		pthread_mutex_unlock(data->right_fork);
		print_msg(data,"is sleeping\n");
		usleep(data->philo->sleep_time * 1000);
	}
	return (0);
}

bool	thread_init(t_data *data, t_philo *info)
{
	int	i;

	i = 0;
	info->start_time = set_time();
	while (i < info->philo_nbr)
	{
		data[i].is_full = false;
		data[i].philo = info;
		data[i].id = i;
		data[i].meals_eaten = 0;
		data[i].start_time = info->start_time;
		data[i].last_meal = info->start_time;
		data[i].left_fork = &info->forks[i];
		data[i].right_fork = &info->forks[(i + 1) % info->philo_nbr];
		if (pthread_mutex_init(&data[i].last_meal_m, NULL))
			return (false);
		if (pthread_create(&data[i].thread, NULL, routine, &data[i]) != 0)
			return (false);
		i++;
	}
	if (pthread_create(&info->died, NULL, monitoring, data) != 0)
		return (false);
	if (pthread_create(&info->meal_limit_t, NULL, eat_limit, data) != 0)
		return (false);
	return (true);
}
