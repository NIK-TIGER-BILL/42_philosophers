#include "../includes/philo.h"

void	ft_clear(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->config.count_philo)
		pthread_mutex_destroy(&data->philos[i].r_fork);
	pthread_mutex_destroy(&data->config.print_mutex);
	free(data->philos);
}

int	ft_error_exit(t_data *data, int flag_clear)
{
	if (flag_clear)
		ft_clear(data);
    ft_putstr_err(ERROR_MSG);
	return (1);
}

int	ft_init_philos(t_data *data)
{
	int	i;

	data->philos = (t_philo *)ft_calloc(data->config.count_philo, sizeof(t_philo));
	if (!data->philos)
		return (1);
    i = -1;
    while (++i < data->config.count_philo)
	{
		data->philos[i].order = i;
		data->philos[i].config = &data->config;
        data->philos[i].l_fork = &data->philos[(i + 1) % data->config.count_philo].r_fork;
		if (pthread_mutex_init(&data->philos[i].r_fork, 0))
			return (1);
	}
	if (pthread_mutex_init(&data->config.print_mutex, 0))
		return (1);
	return (0);
}

int	ft_init_config(t_data *data, int argc, char **argv)
{
	data->config.count_philo = ft_atoi_philo(argv[1]);
	data->config.time_die = ft_atoi_philo(argv[2]);
	data->config.time_eat = ft_atoi_philo(argv[3]);
	data->config.time_sleep = ft_atoi_philo(argv[4]);
    if (data->config.count_philo < 1 || data->config.time_die == -1 || data->config.time_eat == -1 || data->config.time_sleep == -1)
        return (1);
	if (argc == 6)
    {
        data->config.count_eat = ft_atoi_philo(argv[5]);
        if (data->config.count_eat < 1)
            return (1);
    }
    else
		data->config.count_eat = -1;
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
		return (ft_error_exit(&data, 0));
	memset(&data, 0, sizeof(t_data));
	if (ft_init_config(&data, argc, argv))
		return (ft_error_exit(&data, 0));
	if (ft_init_philos(&data))
		return (ft_error_exit(&data, 1));
	if (ft_simulation(&data))
		return (ft_error_exit(&data, 1));
	ft_clear(&data);
	return (0);
}
