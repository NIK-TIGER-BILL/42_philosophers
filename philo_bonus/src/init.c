#include "../includes/philo_bonus.h"

int	ft_init_sem(t_data *data)
{
	sem_unlink("fork");
	data->config.sem_fork = sem_open("fork", O_CREAT, 0644, data->config.count_philo);
	sem_unlink("print");
	data->config.sem_print = sem_open("print", O_CREAT, 0644, 1);
	sem_unlink("dead");
	data->config.sem_dead = sem_open("dead", O_CREAT, 0644, 0);
	if (data->config.sem_fork == SEM_FAILED || data->config.sem_print == SEM_FAILED || data->config.sem_dead == SEM_FAILED)
		return (1);
	return (0);
}

int	ft_init_philos(t_data *data)
{
	int		i;

	data->philos = (t_philo *)ft_calloc(data->config.count_philo, sizeof(t_philo));
	if (!data->philos)
		return (1);
	sem_unlink("eats");
    i = -1;
	while (++i < data->config.count_philo)
	{
		data->philos[i].order = i;
		data->philos[i].config = &data->config;
		data->philos[i].sem_eats = sem_open("eats", O_CREAT, 0644, 0);
		if (data->philos[i].sem_eats == SEM_FAILED)
			return (1);
	}
	if (ft_init_sem(data))
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
