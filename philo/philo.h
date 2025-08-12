/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azorlutu <azorlutu@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:50:08 by azorlutu          #+#    #+#             */
/*   Updated: 2025/03/27 12:50:08 by azorlutu         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define PHILO_MAX_COUNT 200

# define ERR_ARGS 1
# define ERR_MALLOC 2
# define ERR_MUTEX 3
# define ERR_THREAD 4
# define ERR_TIME 5

typedef unsigned long long	t_time;

typedef struct s_mutexes
{
	pthread_mutex_t	*death_mutex;
	pthread_mutex_t	*meals_mutex;
	pthread_mutex_t	*print_mutex;
	int				*life_state;
}	t_mutexes;

typedef struct s_data
{
	pthread_t		monitor_thread;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	meals_mutex;
	pthread_mutex_t	print_mutex;
	int				life_state;
}	t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_eaten;
	int				must_eat_count;
	int				philosophers_count;
	t_time			last_meal_time;
	t_time			born_time;
	t_mutexes		mutexes;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

t_time	get_current_time(void);

int		ft_atoi(const char *str);
int		error_message(const char *str, int signal);
int		init_mutexes(t_philo *philos, t_data *data, char **argv);
int		start_simuation(t_philo *philos, t_data *data, char **argv);
int		init_philo_datas(t_philo *philos, pthread_mutex_t *forks,
			t_data *data, char **argv);
int		check_args(int argc, char **argv);

long	ft_strlen(const char *s);

void	print_state(t_philo *philo, char *msg);
void	ft_sleep(t_time time);
void	*philosophers_routine(void *arg);
void	*monitor_routine(void *arg);
void	ft_free(t_philo *philo, pthread_mutex_t *forks, t_data *data);

#endif