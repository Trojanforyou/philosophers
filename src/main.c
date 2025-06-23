/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msokolov <msokolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:40:18 by msokolov          #+#    #+#             */
/*   Updated: 2025/06/23 21:11:16 by msokolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int main(int ac, char **av)
{
	t_philo info; // общая конфигурация (глобальные настройки симуляции)
	t_data	*data; // основной масив для работы симуляции 
	int i; 

	i = 0;
	data = 0;
	if (!philo_args(&info, ac, av)) 
		return(0);
	if (!malloc_all(&info, &data))
		return (0);
	if (!thread_init(data, &info))
		return (0);
	while (i < info.philo_nbr)
	{
		if(pthread_join(data[i].thread, NULL))
			return (false);
		i++;
	}
	pthread_join(info.died, NULL);
	destroy_all(data, &info);
}
