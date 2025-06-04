/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msokolov <msokolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:40:04 by msokolov          #+#    #+#             */
/*   Updated: 2025/06/04 20:34:25 by msokolov         ###   ########.fr       */
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
# include <limits.h>

typedef struct s_philo
{
	long			philo_nbr;
	long			die_time;
	long			eat_time;
	long			sleep_time;
	long			last_meal;
	long			meal_limit;
}	t_philo;

typedef struct t_data
{
	t_philo			*philos;
	int				id;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;
	bool			died;
	long			start_time;
}	s_data;


bool	philo_init(t_philo *data, int ac, char **av);
int		parse(int ac, char **av);
int		ft_atoi(const char *nptr);
