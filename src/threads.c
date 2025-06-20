/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msokolov <msokolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:04:14 by msokolov          #+#    #+#             */
/*   Updated: 2025/06/20 19:22:18 by msokolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*monitoring(void *args)
{
	t_data *data;
	data = (t_data *)args;
	long long time;
	int i;

	while (1)
	{
		i = 0;
		time = set_time();

		while (i < data->philo->philo_nbr)
		{
			pthread_mutex_lock(&data[i].last_meal_m);
			if (time - data[i].last_meal > data->philo->die_time)
			{
				pthread_mutex_unlock(&data[i].last_meal_m);
				pthread_mutex_lock(&data[i].died_mutex);
				data->philo->elimination = true;
				pthread_mutex_unlock(&data[i].died_mutex);
				printf(RED"Philosopher Has Died\n"RESET);
				return (0);
			}
			else
			pthread_mutex_unlock(&data[i].last_meal_m);
			i++;
		}
		usleep(1000);
	}
	return (0);
}

void	*routine(void *args)
{
	t_data *data;
	data = (t_data *)args;
	while (data->meals_eaten < data->philo->meal_limit || data->philo->elimination == false)
	{
		// if(monitoring(data))
		// 	return (0);
		printf(ORANGE"Philosopher Is Thinking\n"RESET);
		deadlock_case(data);
		data->last_meal = set_time();
		printf(GREEN"Philosopher Is Eating\n"RESET);
		usleep(data->philo->eat_time * 1000);
		data->meals_eaten++;
		// printf("Meals eaten by Philosopher %d: %ld\n", data->id + 1, data->meals_eaten);
		pthread_mutex_unlock(data->left_fork);
		pthread_mutex_unlock(data->right_fork);
		printf(PINK"Philosopher Is Sleeping\n"RESET);
		usleep(data->philo->sleep_time * 1000);
		// printf(GREEN"%ld\n", data->philo->sleep_time);
		// if (data->philo->meal_limit)
		// нужно остановить луп и выйти с сообщением meal_limit
		// if (data->died)
		// выходим из лупа так как он умер
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
		data[i].philo = info;
		data[i].id = i;
		data[i].meals_eaten = 0;
		data[i].start_time = info->start_time;
		data[i].last_meal = info->start_time; // время последнего приема пищи равен началу. Когда я захожу в рутину. Что означает что все философы будут сытые
		data[i].left_fork = &info->forks[i];
		data[i].right_fork = &info->forks[(i + 1) % info->philo_nbr];
		if (pthread_mutex_init(&data[i].died_mutex, NULL))
			return (false);
		if (pthread_mutex_init(&data[i].last_meal_m, NULL))
			return (false);
		if (pthread_create(&data[i].thread, NULL, routine, &data[i]) != 0)
			return (false);
			// printf("Philosopher %d forks: left %p, right %p\n", i, data[i].left_fork, data[i].right_fork);
		i++;
	}
	if (pthread_create(&info->died, NULL, monitoring, data) != 0)
		return (false);
	return (true);
}
