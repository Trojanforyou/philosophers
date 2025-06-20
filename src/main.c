/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msokolov <msokolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:40:18 by msokolov          #+#    #+#             */
/*   Updated: 2025/06/20 19:18:45 by msokolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int main(int ac, char **av)
{
	t_philo info;
	t_data	*data;
	int i;

	i = 0;
	data = 0;
	// if (!parse(ac, av))
	// 	return (0);
	if (!philo_args(&info, ac, av))
		return (0);
	if (!malloc_all(&info, &data))
		return (0);
	if (!thread_init(data, &info))
		return (0);
	while (i < info.philo_nbr)
	{
		if(pthread_join(data[i].thread, NULL))
			return (false);
		printf("here\n");
		i++;
	}
	pthread_join(info.died, NULL);
	// pthread_create(&monitor_thread, NULL, monitoring, monitor);
}
