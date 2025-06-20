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
void	*deadlock_case(void *args)
{
	t_data *data;

	data = (t_data *)args;

	if (data->id % 2 == 0)
	{
		pthread_mutex_lock(data->right_fork);
		printf(YELLOW"Philosopher Has Taken A Right Fork\n"RESET);
		printf(BLUE"Philpsopher Has Taken A Left Fork\n"RESET);
		pthread_mutex_lock(data->left_fork);
	}
	else
	{
		pthread_mutex_lock(data->left_fork);
		printf(BLUE"Philpsopher Has Taken A Left Fork\n"RESET);
		pthread_mutex_lock(data->right_fork);
		printf(YELLOW"Philosopher Has Taken A Right Fork\n"RESET);
	}
	return (0);
}
