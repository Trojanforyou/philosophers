/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msokolov <msokolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:35:52 by msokolov          #+#    #+#             */
/*   Updated: 2025/06/07 21:00:57 by msokolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	parse(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	if (ac != 5 && ac != 6)
	{
		printf("Number of arguments is not correct\n");
		return (0);
	}
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] == '-' || av[i][j] < '0' || av[i][j] > '9' || av[i][j] == ' ')
			{
				printf("Argument type is incorrect\n");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
bool	philo_args(t_philo *info, int ac, char **av)
{
	if (!parse(ac, av))
		return (false);
	info->philo_nbr = ft_atoi(av[1]);
	info->die_time = ft_atoi(av[2]);
	info->eat_time = ft_atoi(av[3]);
	info->sleep_time = ft_atoi(av[4]);
	if (info->philo_nbr >= 2000)
		return(printf("To much philos\n"), false);
	if (ac == 6)
		info->meal_limit = ft_atoi(av[5]);
	else if (ac == 5)
	{
		info->meal_limit = -1;
	}
	if (!info->philo_nbr || !info->die_time || !info->eat_time || !info->sleep_time || !info->meal_limit)
		return (false);
	return (true);
}
int	philo_malloc(t_data **data, t_philo *info)
{
	data = malloc(sizeof(t_data) * info->philo_nbr);
	if (!data)
		return (0);
	return (1);
}
bool	malloc_fork(t_philo *info)
{
	int	i;

	i = 0;
	info->forks = malloc(sizeof(pthread_mutex_t) * info->philo_nbr);
	if (!info->forks)
		return (false);
	while (i <= info->philo_nbr - 1)
	{
		// pthread_mutex_init(&info->forks[i], NULL);
		if (!pthread_mutex_init(&info->forks[i], NULL))
			return (false);
		i++;
	}
	return (true);
}
bool	philo_init(t_data *data)
{
	int	i;

	i = 0;
	while (i <= data->philo->philo_nbr - 1)
	{
		data[i].id = i;
		data[i].left_fork = &data->philo->forks[i];
		data[i].right_fork = &data->philo->forks[(i + 1) % data->philo->philo_nbr];
		data[i].died = false;
		
	}
}
