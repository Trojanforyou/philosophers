/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msokolov <msokolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:40:18 by msokolov          #+#    #+#             */
/*   Updated: 2025/06/04 18:25:31 by msokolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int main(int ac, char **av)
{
	t_philo data;
	if (!philo_init(&data, ac, av))
		return (0);
	printf("%ld ", data.philo_nbr);
	printf("%ld ", data.die_time);
	printf("%ld ", data.eat_time);
	printf("%ld ", data.sleep_time);
	printf("%ld ", data.meal_limit);
}
