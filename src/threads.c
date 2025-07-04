/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msokolov <msokolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:04:14 by msokolov          #+#    #+#             */
/*   Updated: 2025/07/04 16:56:18 by msokolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitoring(void *args)
{
	t_data	*data;
	int		i;

	data = (t_data *)args;
	while (1)
	{
		i = -1;
		while (++i < data->philo->philo_nbr)
		{
			if (!died(data))
				return (0);
			if (!eat_limit(data))
				return (0);
		}
		usleep(1000);
	}
}

void	*routine(void *args)
{
	t_data	*data;

	data = (t_data *)args;
	usleep((data->id % 2) * (data->philo->eat_time * 1000));
	while (is_simulation_running(data))
	{
		print_msg(data, "is thinking\n");
		if (data->philo->philo_nbr == 1)
			return (alone_filo(data), NULL);
		if (data->philo->philo_nbr % 2 == 1)
			usleep(1000);
		deadlock_case(data);
		print_msg(data, "is eating\n");
		pthread_mutex_lock(&data->philo->meal_mutex);
		data->meals_eaten++;
		pthread_mutex_unlock(&data->philo->meal_mutex);
		usleep(data->philo->eat_time * 1000);
		pthread_mutex_unlock(data->left_fork);
		pthread_mutex_unlock(data->right_fork);
		print_msg(data, "is sleeping\n");
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
		if (!data[i].right_fork || !data[i].left_fork)
			return (destroy_all(data, info), 0);
		if (pthread_mutex_init(&data[i].last_meal_m, NULL))
			return (false);
		if (pthread_create(&data[i].thread, NULL, routine, &data[i]) != 0)
			return (false);
		i++;
	}
	if (pthread_create(&info->died, NULL, monitoring, data) != 0)
		return (false);
	return (true);
}

bool	eat_limit(t_data *data)
{
	int	counter;
	int	i;

	counter = 1;
	i = -1;
	while (++i < data->philo->philo_nbr)
	{
		pthread_mutex_lock(&data->philo->meal_mutex);
		if (data[i].meals_eaten >= data->philo->meal_limit)
		{
			counter++;
			pthread_mutex_unlock(&data->philo->meal_mutex);
		}
		else
			pthread_mutex_unlock(&data->philo->meal_mutex);
	}
	if (counter > data->philo->philo_nbr && data->philo->meal_limit != -1)
	{
		pthread_mutex_lock(&data->philo->died_mutex);
		data->philo->elimination = true;
		pthread_mutex_unlock(&data->philo->died_mutex);
		printf("eat limit\n");
		return (false);
	}
	return (true);
}

void	alone_filo(t_data *data)
{
	pthread_mutex_lock(data->left_fork);
	print_msg(data, "has taken a fork\n");
	pthread_mutex_unlock(data->left_fork);
}
