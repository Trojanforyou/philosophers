/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msokolov <msokolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:40:04 by msokolov          #+#    #+#             */
/*   Updated: 2025/07/02 15:56:16 by msokolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_H
# define PHILO_H
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define PURPLE "\033[35m"
#define PINK "\033[95m"
#define ORANGE "\033[38;5;208m"
#define BLUE "\33[34m"
#define RESET "\033[0m"
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
	long long		eat_time;
	long			sleep_time;
	bool 			elimination;
	long			meal_limit;
	long			start_time;
	pthread_t		meal_limit_t;
	pthread_mutex_t print_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t died_mutex;
	pthread_t		died;
	pthread_mutex_t	*forks;
}	t_philo;

typedef struct s_data
{
	int				id;
	bool			is_full;
	long			meals_eaten;
	long long		last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread;
	pthread_mutex_t last_meal_m;
	long			start_time;
	t_philo			*philo;
}	t_data;


int		parse(int ac, char **av);
int		ft_atoi(const char *nptr);
int		philo_malloc(t_data **data, t_philo *info);

long long	set_time(void);

bool	philo_args(t_philo *info, int ac, char **av);
bool	malloc_fork(t_philo *info);
bool	thread_init(t_data *data, t_philo *info);
bool	malloc_all(t_philo *info, t_data **data);
bool 	is_simulation_running(t_data *data);
bool	eat_limit(t_data *data);

void	*deadlock_case(void *args);
void	*routine(void	*args);
void	*monitoring(void *args);
void	print_msg(t_data *data, char *msg);
void 	destroy_all(t_data *data, t_philo *info);
