



#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	long	res;

	i = 0;
	res = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + (nptr[i] - '0');
		if (res > INT_MAX)
			return (0);
		i++;
	}
	return (res);
}
// Если вилку будет брать четный филосов. То тогда первым он берет правую вилку. И наоборот если левую
void	*deadlock_case(void *args)
{
	t_data *data;

	data = (t_data *)args;

	if (data->id % 2 == 0)
	{
		pthread_mutex_lock(data->right_fork);
		print_msg(data,"has taken a fork\n");
		pthread_mutex_lock(data->left_fork);
		print_msg(data,"has taken a fork\n");
	}
	else
	{
		pthread_mutex_lock(data->left_fork);
		print_msg(data,"has taken a fork\n");
		pthread_mutex_lock(data->right_fork);
		print_msg(data,"has taken a fork\n");
	}
	pthread_mutex_lock(&data->last_meal_m);
	data->last_meal = set_time();
	pthread_mutex_unlock(&data->last_meal_m);
	return (0);
}

bool is_simulation_running(t_data *data)
{
	bool running;
	pthread_mutex_lock(&data->philo->died_mutex);
	running = !data->philo->elimination;
	pthread_mutex_unlock(&data->philo->died_mutex);
	return (running);
}

void	print_msg(t_data *data, char *msg)
{
	if (is_simulation_running(data))
		printf("%lld %d %s", set_time() - data->philo->start_time, data->id + 1, msg);
}

void destroy_all(t_data *data, t_philo *info)
{
	int i = 0;
	if (info->forks)
	{
		while (i < info->philo_nbr)
		{
			pthread_mutex_destroy(&info->forks[i]);
			i++;
		}
		free(info->forks);
	}
	// if (&info->died_mutex)
	// 	pthread_mutex_destroy(&info->died_mutex);
	// if (&data->last_meal_m)
	// 	pthread_mutex_destroy(&data->last_meal_m);
	free(data);
}
