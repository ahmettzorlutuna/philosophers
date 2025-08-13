/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azorlutu <azorlutu@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 23:20:47 by azorlutu          #+#    #+#             */
/*   Updated: 2025/04/23 23:20:48 by azorlutu         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	int	is_philo_dead(t_philo *philo, int i)
{
	t_time	current_time;

	pthread_mutex_lock(philo[i].mutexes.meals_mutex);
	current_time = get_current_time() - philo[i].last_meal_time;
	if (current_time > (t_time)philo[i].time_to_die)
	{
		pthread_mutex_lock(philo[i].mutexes.death_mutex);
		*philo[i].mutexes.life_state = 0;
		pthread_mutex_lock(philo[i].mutexes.print_mutex);
		printf("%llu %d died\n", (get_current_time()
				- philo[i].born_time), i + 1);
		pthread_mutex_unlock(philo[i].mutexes.print_mutex);
		pthread_mutex_unlock(philo[i].mutexes.death_mutex);
		pthread_mutex_unlock(philo[i].mutexes.meals_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo[i].mutexes.meals_mutex);
	return (0);
}

static int	is_all_meals_eaten(t_philo *philo, int total_meals_eaten)
{
	if ((total_meals_eaten >= (philo->philosophers_count
				* philo->must_eat_count)) && philo->must_eat_count != -1)
	{
		pthread_mutex_lock(philo[0].mutexes.death_mutex);
		*philo[0].mutexes.life_state = 0;
		pthread_mutex_unlock(philo[0].mutexes.death_mutex);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philo;
	int		i;
	int		total_meals_eaten;

	philo = (t_philo *)arg;
	while (1)
	{
		i = 0;
		total_meals_eaten = 0;
		while (i < philo->philosophers_count)
		{	
			if (is_philo_dead(philo, i))
				return (NULL);
			pthread_mutex_lock(philo[i].mutexes.meals_mutex);
			total_meals_eaten += philo[i].meals_eaten;
			pthread_mutex_unlock(philo[i].mutexes.meals_mutex);
			i++;
		}
		if (is_all_meals_eaten(philo, total_meals_eaten))
			return (NULL);
		ft_sleep(1);
	}
	return (NULL);
}
