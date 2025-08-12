/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azorlutu <azorlutu@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:36:08 by azorlutu          #+#    #+#             */
/*   Updated: 2025/04/05 15:36:11 by azorlutu         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(t_time time)
{
	t_time	start_time;

	start_time = get_current_time();
	while (get_current_time() - start_time < time)
		usleep(200);
}

int	error_message(const char *str, int signal)
{
	if (str)
		write(2, str, ft_strlen(str));
	return (signal);
}

t_time	get_current_time(void)
{
	t_time			time;
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		error_message("Time error\n", ERR_TIME);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

void	print_state(t_philo *philo, char *msg)
{
	size_t	current_time;

	current_time = get_current_time() - philo->born_time;
	pthread_mutex_lock(philo->mutexes.death_mutex);
	if (*philo->mutexes.life_state == 1)
	{
		pthread_mutex_unlock(philo->mutexes.death_mutex);
		pthread_mutex_lock(philo->mutexes.print_mutex);
		printf("%ld %d %s\n", current_time, philo->id + 1, msg);
		pthread_mutex_unlock(philo->mutexes.print_mutex);
	}
	else
		pthread_mutex_unlock(philo->mutexes.death_mutex);
}

void	ft_free(t_philo *philo, pthread_mutex_t *forks, t_data *data)
{
	int	i;

	pthread_mutex_destroy(&data->meals_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	i = 0;
	while (i < philo->philosophers_count)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(philo);
	free(forks);
}
