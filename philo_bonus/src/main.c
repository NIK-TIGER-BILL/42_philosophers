#include "philo_bonus.h"

void	ft_clear(t_data *data)
{
	int	i;

	sem_close(data->config.sem_dead);
	sem_close(data->config.sem_print);
	sem_close(data->config.sem_fork);
	i = 0;
	while (i < data->config.count_philo)
	{
		sem_close(data->philos[i].sem_eats);
		i++;
	}
	free(data->philos);
}

int	ft_error_exit(t_data *data, int code_ex)
{
	if (code_ex == 1)
		ft_clear(data);
	write(2, "Error\n", 6);
	return (code_ex);
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
