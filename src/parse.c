/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msokolov <msokolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:35:52 by msokolov          #+#    #+#             */
/*   Updated: 2025/06/18 18:25:23 by msokolov         ###   ########.fr       */
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
		printf(RED"Number Of Arguments Is Incorrect\n" RESET);
		return (0);
	}
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] == '-' || av[i][j] < '0' || av[i][j] > '9' || av[i][j] == ' ')
			{
				printf(RED"Argument Type Is Incorrect\n"RESET);
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
		return (0);
	info->philo_nbr = ft_atoi(av[1]);
	info->die_time = ft_atoi(av[2]);
	info->eat_time = ft_atoi(av[3]);
	info->sleep_time = ft_atoi(av[4]);
	if (ac == 6)
		info->meal_limit = ft_atoi(av[5]);
	else if (ac == 5)
	{
		info->meal_limit = -1;
	}
	if (info->philo_nbr >= 200)
		return(printf(RED"To Much Philos\n" RESET), false);
	if (info->philo_nbr <= 0 ||info->die_time <= 0|| info->eat_time <= 0|| info->sleep_time <= 0)
		return (false);
	if (ac == 6 && info->meal_limit <= 0)
		return (false);
	return (true);
}
int	philo_malloc(t_data **data, t_philo *info)
{
	*data = malloc(sizeof(t_data) * info->philo_nbr);
	if (!*data)
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
	while (i < info->philo_nbr)
	{
		// pthread_mutex_init(&info->forks[i], NULL);
		if (pthread_mutex_init(&info->forks[i], NULL))
			return (false);
		i++;
	}
	return (true);
}

bool	malloc_all(t_philo *info, t_data **data)
{
	if (!malloc_fork(info))
		return (false);
	if (!philo_malloc(data, info))
		return (false);
	return (true);
}
