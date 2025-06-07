/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msokolov <msokolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:40:04 by msokolov          #+#    #+#             */
/*   Updated: 2025/06/07 18:38:54 by msokolov         ###   ########.fr       */
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
	pthread_mutex_t	*forks;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	bool			died;
	long			start_time;
	t_philo			*philo;
	struct s_data	*next;
}	t_data;


bool	philo_args(t_philo *info, int ac, char **av);
int		parse(int ac, char **av);
int		ft_atoi(const char *nptr);
bool	malloc_fork(t_philo *info);
int		philo_malloc(t_data **data, t_philo *info);
