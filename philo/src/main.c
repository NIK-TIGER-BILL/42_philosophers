#include "philo.h"

void	ft_clear(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->config.count_philo)
	{
		pthread_mutex_destroy(&data->philos[i].r_fork);
		i++;
	}
	pthread_mutex_destroy(&data->config.print_mutex);
	free(data->philos);
}

int	ft_error_exit(t_data *data, int code_ex)
{
	if (code_ex == 1)
		ft_clear(data);
	write(2, "Error\n", 6);
	return (code_ex);
}

int	ft_init_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philos = (t_philo *)ft_calloc(data->config.count_philo, \
														sizeof(t_philo));
	if (data->philos == NULL)
		return (1);
	while (i < data->config.count_philo)
	{
		data->philos[i].order = i;
		data->philos[i].config = &data->config;
		if (i + 1 == data->config.count_philo)
			data->philos[i].l_fork = &data->philos[0].r_fork;
		else
			data->philos[i].l_fork = &data->philos[i + 1].r_fork;
		if (pthread_mutex_init(&data->philos[i].r_fork, NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->config.print_mutex, NULL))
		return (1);
	return (0);
}

int	ft_init_config(t_data *data, int argc, char **argv)
{
	if (!ft_check_isdigit(argv))
		return (1);
	data->config.count_philo = ft_atoi_philo(argv[1]);
	data->config.time_die = ft_atoi_philo(argv[2]);
	data->config.time_eat = ft_atoi_philo(argv[3]);
	data->config.time_sleep = ft_atoi_philo(argv[4]);
	if (argc == 6)
		data->config.count_eat = ft_atoi_philo(argv[5]);
	if (argc == 5)
	{
		if (data->config.count_philo < 1 || data->config.count_philo > 200 || \
		data->config.time_die < 60 || data->config.time_eat < 60 || \
		data->config.time_sleep < 60)
			return (1);
		data->config.count_eat = -1;
	}
	if (argc == 6)
	{
		if (data->config.count_eat < 1)
			return (1);
	}
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
