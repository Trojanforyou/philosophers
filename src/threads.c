/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msokolov <msokolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:04:14 by msokolov          #+#    #+#             */
/*   Updated: 2025/06/17 18:09:20 by msokolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*routine(void *args)
{
	t_philo *info;
	info = (t_philo *)args;
	while (1)
	{
		printf(GREEN"Philosopher Is Thinking\n"RESET);
		pthread_mutex_lock(info->data->left_fork);
		printf(GREEN"Philpsopher Has Taken A Fork"RESET);
		pthread_mutex_lock(info->data->right_fork);
		printf(GREEN"Philosopher Has Taken A Fork"RESET);
		info->data->last_meal = set_time();
		printf(GREEN"Philosopher Is Eating"RESET);
		usleep(info->eat_time * 1000);
		info->data->meals_eaten++;
		pthread_mutex_unlock(info->data->left_fork);
		pthread_mutex_unlock(info->data->right_fork);
		printf(GREEN"Philosopher Is Sleeping"RESET);
		// if (info->meal_limit || info->data->died == true)
		// 	break ;
	}
}


bool	thread_init(t_data *data, t_philo *info)
{
	int	i;

	i = 0;
	info->start_time = set_time();
	while (i <= data->philo->philo_nbr - 1)
	{
		data[i].id = i;
		data[i].left_fork = &data->philo->forks[i];
		data[i].right_fork = &data->philo->forks[(i + 1) % data->philo->philo_nbr];
		data[i].philo = info;
		if (pthread_create(&data[i].thread, NULL, routine, &data[i]) != 0)
			return (false);
		i++;
	}
	return (true);

}
