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
	time_t			lim_die;
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
int		ft_check_isdigit(char **argv);
void	*ft_calloc(size_t count, size_t size);
void	ft_print_message(t_philo *philo, char *message);
int		ft_init_config(t_data *data, int argc, char **argv);
int		ft_init_philos(t_data *data);
int		ft_simulation(t_data *data);

#endif
