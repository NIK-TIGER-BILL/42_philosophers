#include "../includes/philo.h"

void	ft_print_message(t_philo *philo, char *message)
{
    pthread_mutex_lock(&philo->config->print_mutex);
    if (!philo->config->stop)
        printf(message, ft_get_time() - philo->config->start_time, philo->order + 1);
	pthread_mutex_unlock(&philo->config->print_mutex);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(&philo->r_fork);
    ft_print_message(philo, TAKE_FORK);
    ft_print_message(philo, TAKE_FORK);
	ft_print_message(philo, EAT);
	philo->last_eat = ft_get_time();
	usleep(philo->config->time_eat * 1000);
    if (++philo->count_eat == philo->config->count_eat)
        philo->config->all_eat++;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(&philo->r_fork);
}

void    ft_monitor(t_philo *philo)
{
	while (1)
	{
		usleep(1000);
		if (!philo->config->stop && ft_get_time() > philo->last_eat + philo->config->time_die)
		{
            ft_print_message(philo, DIED);
			philo->config->stop = 1;
			return;
		}
		if (philo->config->all_eat == philo->config->count_philo)
		{
			philo->config->stop = 1;
			return;
		}
	}
}

void    ft_monitor(t_philo *philo)
{
	while (1)
	{
		usleep(1000);
		if (!philo->config->stop && ft_get_time() > philo->last_eat + philo->config->time_die)
		{
            ft_print_message(philo, DIED);
			philo->config->stop = 1;
			return;
		}
		if (philo->config->all_eat == philo->config->count_philo)
		{
			philo->config->stop = 1;
			return;
		}
	}
}

//void    ft_monitor(t_philo *philos)
//{
//    int i;
//
//	while (1)
//	{
//		usleep(1000);
//        i = -1;
//        while (++i < philos->config->count_philo)
//        {
//            if (!philos->config->stop && ft_get_time() > philos[i].last_eat + philos[i].config->time_die)
//            {
//                philos->config->stop = 1;
//                pthread_mutex_lock(&philos->config->print_mutex);
//                printf(DIED, ft_get_time() - philos->config->start_time, philos[i].order + 1);
//                pthread_mutex_unlock(&philos->config->print_mutex);
//                return;
//            }
//            if (philos->config->all_eat == philos->config->count_philo)
//            {
//                philos->config->stop = 1;
//                return;
//            }
//        }
//	}
//}

void	*ft_philos_live(t_philo *philo)
{
	pthread_t	tid;

	philo->last_eat = ft_get_time();
	if (pthread_create(&tid, 0, (void *)ft_monitor, philo))
		return ((void *)1);
	if (pthread_detach(tid))
		return ((void *)1);
	if (!(philo->order % 2))
		usleep(1000);
	while (!philo->config->stop && philo->config->all_eat != philo->config->count_philo)
	{
        if (philo->config->count_philo > 1)
		{
			ft_eat(philo);
			ft_print_message(philo, SLEEP);
			usleep(philo->config->time_sleep * 1000);
			ft_print_message(philo, THINK);
		}
	}
	return ((void *)0);
}

int	ft_simulation(t_data *data)
{
	int	i;
//    pthread_t	tid;

    i = -1;
    data->config.start_time = ft_get_time();
    while (++i < data->config.count_philo)
	{
		if (pthread_create(&data->philos[i].tid, 0, (void *)ft_philos_live, &(data->philos[i])))
			return (1);
		usleep(100);
	}
//    if (pthread_create(&tid, 0, (void *)ft_monitor, data->philos))
//        return (1);
	i = -1;
	while (++i < data->config.count_philo)
	{
		if (pthread_join(data->philos[i].tid, 0))
			return (1);
		usleep(100);
	}
//    if (pthread_detach(tid))
//        return (1);
	return (0);
}
