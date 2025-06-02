/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msokolov <msokolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:40:04 by msokolov          #+#    #+#             */
/*   Updated: 2025/06/02 18:14:53 by msokolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_H
# define PHILO_H
#endif

# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct s_philo
{
	int				id;			//philo id
	long			philo_nbr;
	long			die_time;
	long			eat_time;
	long			sleep_time;
	long			last_meal;
	long			meal_limit;
	long			start_time;
	bool			died;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;
}	t_philo;


int	parse(int ac, char **av);
