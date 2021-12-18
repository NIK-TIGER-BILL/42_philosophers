#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# define THINKING " \033[1;32m%6lu %3d   is thinking\n\033[0m"
# define TAKEN_FORK " \033[1;37m%6lu %3d   has taken a fork\n\033[0m"
# define SLEEPING " \033[1;34m%6lu %3d   is sleeping\n\033[0m"
# define EATING " \033[1;33m%6lu %3d   is eating\n\033[0m"
# define DIED " \033[1;31m%6lu %3d   died\n\033[0m"

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
	time_t			lim_die;
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
int		ft_check_isdigit(char **argv);
void	*ft_calloc(size_t count, size_t size);
int		ft_simulation(t_data *data);

#endif
