/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalsami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 15:03:23 by ebalsami          #+#    #+#             */
/*   Updated: 2022/01/09 15:03:24 by ebalsami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <fcntl.h>
# include <signal.h>

# define THINK " \e[1;32m%6lu %4d    is thinking\n\e[0m"
# define TAKE_FORK " \e[1;37m%6lu %4d    has taken a fork\n\e[0m"
# define SLEEP " \e[1;34m%6lu %4d    is sleeping\n\e[0m"
# define EAT " \e[1;33m%6lu %4d    is eating\n\e[0m"
# define DIED " \e[1;31m%6lu %4d    died\n\e[0m"
# define ERROR_MSG "\e[1;91m Error\n\e[0m"

typedef struct s_config
{
	int				count_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				count_eat;
	time_t			start_time;
	int				stop;
	int				all_eat;
	sem_t			*sem_fork;
	sem_t			*sem_print;
	sem_t			*sem_dead;
}	t_config;

typedef struct s_philo
{
	int				order;
	int				count_eat;
	time_t			last_eat;
	pid_t			pid;
	sem_t			*sem_eats;
	t_config		*config;
}	t_philo;

typedef struct s_data
{
	t_config	config;
	t_philo		*philos;

}	t_data;

int		ft_atoi_philo(const char *str);
time_t	ft_get_time(void);
void	*ft_calloc(long int count, int size);
void	ft_print_message(t_philo *philo, char *message);
int		ft_init_config(t_data *data, int argc, char **argv);
int		ft_init_philos(t_data *data);
int		ft_simulation(t_data *data);
void	ft_putstr_err(char *str);

#endif
