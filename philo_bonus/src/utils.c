#include "philo_bonus.h"

void	ft_print_message(t_philo *philo, char *message)
{
	time_t	time;

	sem_wait(philo->config->sem_print);
	time = ft_get_time() - philo->config->start_time;
	if (!philo->config->stop && (philo->config->count_eat == -1 || \
				philo->config->all_eat != philo->config->count_philo))
		printf(message, time, philo->order + 1);
	sem_post(philo->config->sem_print);
}

time_t	ft_get_time(void)
{
	struct timeval	tv;
	time_t			res;

	gettimeofday(&tv, NULL);
	res = 1000 * (size_t)tv.tv_sec + (size_t)tv.tv_usec / 1000;
	return (res);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*mem;
	size_t	i;
	size_t	res_count;

	i = 0;
	res_count = count * size;
	mem = (char *)malloc(res_count);
	if (!(mem))
		return (NULL);
	while (res_count--)
	{
		mem[i] = 0;
		i++;
	}
	return (mem);
}

int	ft_check_isdigit(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < 48 || argv[i][j] > 57)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_atoi_philo(const char *str)
{
	size_t		i;
	int			res;
	long long	res_check;

	i = 0;
	res = 0;
	res_check = 0;
	while (str[i] >= 48 && str[i] <= 57)
	{
		res = res * 10 + (str[i] - '0');
		i++;
		if (res < res_check)
			return (-1);
		res_check = res;
	}
	return (res);
}
