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



