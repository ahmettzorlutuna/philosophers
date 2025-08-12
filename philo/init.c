/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azorlutu <azorlutu@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 10:53:32 by azorlutu          #+#    #+#             */
/*   Updated: 2025/04/05 10:53:33 by azorlutu         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo_datas(t_philo *philos, pthread_mutex_t *forks,
				t_data *data, char **argv)
{
	int	i;

	i = -1;
	while (++i < ft_atoi(argv[1]))
	{
		philos[i].id = i;
		philos[i].philosophers_count = ft_atoi(argv[1]);
		philos[i].time_to_die = ft_atoi(argv[2]);
		philos[i].time_to_eat = ft_atoi(argv[3]);
		philos[i].time_to_sleep = ft_atoi(argv[4]);
		philos[i].last_meal_time = get_current_time();
		philos[i].born_time = get_current_time();
		philos[i].meals_eaten = 0;
		philos[i].must_eat_count = -1;
		philos[i].mutexes.life_state = &data->life_state;
		philos[i].mutexes.death_mutex = &data->death_mutex;
		philos[i].mutexes.meals_mutex = &data->meals_mutex;
		philos[i].mutexes.print_mutex = &data->print_mutex;
		if (argv[5])
			philos[i].must_eat_count = ft_atoi(argv[5]);
		philos[i].left_fork = &forks[i];
		philos[i].right_fork = &forks[(i + 1) % ft_atoi(argv[1])];
	}
	return (0);
}

int	init_mutexes(t_philo *philos, t_data *data, char **argv)
{
	int	i;
	int	philos_number;
	int	life_state;

	life_state = 1;
	philos_number = ft_atoi(argv[1]);
	data->life_state = life_state;
	i = -1;
	while (++i < philos_number)
	{
		if (pthread_mutex_init(philos[i].left_fork, NULL) != 0)
			error_message("Mutex initialization failed", ERR_MUTEX);
	}
	if (pthread_mutex_init(&data->meals_mutex, NULL) != 0)
		error_message("Meals mutex initialization failed", ERR_MUTEX);
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		error_message("Print mutex initialization failed", ERR_MUTEX);
	if (pthread_mutex_init(&data->death_mutex, NULL) != 0)
		error_message("Death mutex initialization failed", ERR_MUTEX);
	return (0);
}
