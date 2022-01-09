/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalsami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 15:03:39 by ebalsami          #+#    #+#             */
/*   Updated: 2022/01/09 15:03:40 by ebalsami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	ft_monitor(t_philo *philo)
{
	while (1)
	{
		usleep(1000);
		if (!philo->config->stop && ft_get_time()
			> philo->last_eat + philo->config->time_die)
		{
			philo->config->stop = 1;
			printf(DIED, ft_get_time() - philo->config->start_time,
				philo->order + 1);
			sem_post(philo->config->sem_dead);
			return ;
		}
		sem_post(philo->config->sem_print);
	}
}

void	ft_monitor_eat(t_data *data)
{
	int	i;

	if (data->config.count_eat == -1)
		return ;
	i = -1;
	while (++i < data->config.count_philo)
		sem_wait(data->philos[i].sem_eats);
	sem_post(data->config.sem_dead);
	return ;
}

void	ft_eat(t_philo *philo)
{
	sem_wait(philo->config->sem_fork);
	ft_print_message(philo, TAKE_FORK);
	sem_wait(philo->config->sem_fork);
	ft_print_message(philo, TAKE_FORK);
	ft_print_message(philo, EAT);
	philo->last_eat = ft_get_time();
	if (++philo->count_eat == philo->config->count_eat)
		sem_post(philo->sem_eats);
	usleep(philo->config->time_eat * 1000);
	sem_post(philo->config->sem_fork);
	sem_post(philo->config->sem_fork);
}

int	ft_philos_live(t_philo *philo)
{
	pthread_t	tid;

	philo->last_eat = ft_get_time();
	if (pthread_create(&tid, NULL, (void *)ft_monitor, philo))
		exit(1);
	if (pthread_detach(tid))
		exit(1);
	while (!philo->config->stop)
	{
		ft_eat(philo);
		ft_print_message(philo, SLEEP);
		usleep(philo->config->time_sleep * 1000);
		ft_print_message(philo, THINK);
	}
	exit(0);
}

int	ft_simulation(t_data *data)
{
	int			i;
	pthread_t	tid;

	data->config.start_time = ft_get_time();
	i = -1;
	while (++i < data->config.count_philo)
	{
		data->philos[i].pid = fork();
		if (!data->philos[i].pid)
			ft_philos_live(&data->philos[i]);
		usleep(1000);
	}
	if (pthread_create(&tid, NULL, (void *)ft_monitor_eat, data))
		return (1);
	if (pthread_detach(tid))
		return (1);
	sem_wait(data->config.sem_dead);
	i = -1;
	while (++i < data->config.count_philo)
	{
		sem_post(data->philos[i].sem_eats);
		kill(data->philos[i].pid, SIGKILL);
	}
	return (0);
}
