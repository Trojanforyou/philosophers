/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msokolov <msokolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:35:52 by msokolov          #+#    #+#             */
/*   Updated: 2025/06/02 19:03:37 by msokolov         ###   ########.fr       */
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
		exit(EXIT_FAILURE);
	}
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] == '-' || av[i][j] < '0' || av[i][j] > '9' || av[i][j] == ' ' || av[i][0] == '0')
			{
				printf("Argument type is incorrect\n");
				exit(EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
	return (1);
}
int	philo_init(t_philo *data)
{
	data->died;

}

