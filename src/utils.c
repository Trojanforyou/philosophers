#include <philo.h>

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
		// if (!is_simulation_running(data))
		// 	return (NULL);
		print_msg(data, YELLOW"Philosopher Has Taken A Right Fork\n"RESET);
		pthread_mutex_lock(data->left_fork);
		// if (!is_simulation_running(data))
		// 	return (NULL);
		print_msg(data, BLUE"Philpsopher Has Taken A Left Fork\n"RESET);
	}
	else
	{
		pthread_mutex_lock(data->left_fork);
		// if (!is_simulation_running(data))
		// 	return (NULL);
		print_msg(data, BLUE"Philpsopher Has Taken A Left Fork\n"RESET);
		pthread_mutex_lock(data->right_fork);
		// if (!is_simulation_running(data))
		// 	return (NULL);
		print_msg(data, YELLOW"Philosopher Has Taken A Right Fork\n"RESET);
	}
	return (0);
}

bool is_simulation_running(t_data *data)
{
	bool running;
	pthread_mutex_lock(&data->died_mutex);
	running = !data->philo->elimination;
	pthread_mutex_unlock(&data->died_mutex);
	return (running);
}

void	print_msg(t_data *data, char *msg)
{
	if (!is_simulation_running(data))
		return ;
	printf("%lld %d %s ", set_time() - data->philo->start_time, data->id + 1, msg);
}

void destroy_all(t_data *data, t_philo *info)
{
	int i = 0;
	while (i++ < info->philo_nbr)
	{
		pthread_mutex_destroy(&data[i].died_mutex);
		pthread_mutex_destroy(&data[i].last_meal_m);
	}
	i = 0;
	while (i++ < info->philo_nbr)
		pthread_mutex_destroy(&info->forks[i]);
	pthread_mutex_destroy(&data->died_mutex);
	free(data);
	free(info->forks);
}


