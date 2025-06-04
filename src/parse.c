/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msokolov <msokolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:35:52 by msokolov          #+#    #+#             */
/*   Updated: 2025/06/04 20:01:14 by msokolov         ###   ########.fr       */
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
bool	philo_init(t_philo *data, int ac, char **av)
{
	if (!parse(ac, av))
		return (false);
	data->philo_nbr = ft_atoi(av[1]);
	data->die_time = ft_atoi(av[2]);
	data->eat_time = ft_atoi(av[3]);
	data->sleep_time = ft_atoi(av[4]);
	if (data->philo_nbr >= 2000)
		return(printf("To much philos\n"), false);
	if (ac == 6)
		data->meal_limit = ft_atoi(av[5]);
	else if (ac == 5)
	{
		data->meal_limit = -1;
	}
	if (!data->philo_nbr || !data->die_time || !data->eat_time || !data->sleep_time || !data->meal_limit)
		return (false);
	return (true);
}

