#include "philo.h"

void	ft_print_message(t_philo *philo, char *message)
{
	time_t	time;

	pthread_mutex_lock(&philo->config->print_mutex);
	time = ft_get_time() - philo->config->start_time;
	if (!philo->config->stop && (philo->config->count_eat == -1 || \
				philo->config->all_eat != philo->config->count_philo))
		printf(message, time, philo->order + 1);
	pthread_mutex_unlock(&philo->config->print_mutex);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	ft_print_message(philo, TAKEN_FORK);
	pthread_mutex_lock(&philo->r_fork);
	ft_print_message(philo, TAKEN_FORK);
	ft_print_message(philo, EATING);
	philo->last_eat = ft_get_time();
	philo->lim_die = philo->last_eat + philo->config->time_die;
	if (philo->config->count_eat != -1)
	{
		pthread_mutex_lock(&philo->config->print_mutex);
		philo->count_eat++;
		if (philo->count_eat == philo->config->count_eat)
			philo->config->all_eat++;
		pthread_mutex_unlock(&philo->config->print_mutex);
	}
	usleep(philo->config->time_eat * 1000);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(&philo->r_fork);
}

void	*ft_monitor(t_philo *philo)
{
	time_t	time;

	while (21)
	{
		usleep(1000);
		pthread_mutex_lock(&philo->config->print_mutex);
		time = ft_get_time() - philo->config->start_time;
		if (!philo->config->stop && ft_get_time() > philo->lim_die)
		{
			philo->config->stop = 1;
			printf(DIED, time, philo->order + 1);
			pthread_mutex_unlock(&philo->config->print_mutex);
			return ((void *)0);
		}
		if (philo->config->all_eat == philo->config->count_philo)
		{
			philo->config->stop = 1;
			pthread_mutex_unlock(&philo->config->print_mutex);
			return ((void *)0);
		}
		pthread_mutex_unlock(&philo->config->print_mutex);
	}
	return ((void *)0);
}

void	*ft_philos_live(t_philo *philo)
{
	pthread_t	tid;

	philo->last_eat = ft_get_time();
	philo->lim_die = philo->last_eat + philo->config->time_die;
	if (pthread_create(&tid, NULL, (void *)ft_monitor, philo))
		return ((void *)1);
	if (pthread_detach(tid))
		return ((void *)1);
	if (!(philo->order % 2))
		usleep(1000);
	while (!philo->config->stop && (philo->config->count_eat == -1 || \
				philo->config->all_eat != philo->config->count_philo))
	{
		if (philo->l_fork != &philo->r_fork)
		{
			ft_eat(philo);
			ft_print_message(philo, SLEEPING);
			usleep(philo->config->time_sleep * 1000);
			ft_print_message(philo, THINKING);
		}
	}
	return ((void *)0);
}

int	ft_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->config.count_philo)
	{
		data->philos[i].config->start_time = ft_get_time();
		if (pthread_create(&data->philos[i].tid, NULL, \
								(void *)ft_philos_live, &(data->philos[i])))
			return (1);
		i++;
		usleep(100);
	}
	i = 0;
	while (i < data->config.count_philo)
	{
		if (pthread_join(data->philos[i].tid, NULL))
			return (1);
		i++;
		usleep(100);
	}
	return (0);
}
