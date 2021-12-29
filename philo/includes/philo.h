#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

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
	int				all_eat;
	int				stop;
	time_t			start_time;
	pthread_mutex_t	print_mutex;
}	t_config;

typedef struct s_philo
{
	int				order;
	int				count_eat;
	time_t			last_eat;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	r_fork;
	pthread_t		tid;
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
int		ft_simulation(t_data *data);
void    ft_putstr_err(char *str);

#endif
