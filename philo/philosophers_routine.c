/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_routine.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azorlutu <azorlutu@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 23:18:31 by azorlutu          #+#    #+#             */
/*   Updated: 2025/04/23 23:18:33 by azorlutu         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	int	check_death(t_philo *philo)
{
	pthread_mutex_lock(philo->mutexes.death_mutex);
	if (*philo->mutexes.life_state == 0)
	{
		pthread_mutex_unlock(philo->mutexes.death_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->mutexes.death_mutex);
	return (0);
}

static void	philo_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, " has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_state(philo, " has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_state(philo, " has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, " has taken a fork");
	}
	print_state(philo, " is eating");
	pthread_mutex_lock(philo->mutexes.meals_mutex);
	philo->last_meal_time = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->mutexes.meals_mutex);
	ft_sleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*philosophers_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->philosophers_count == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, " has taken a fork");
		ft_sleep(philo->time_to_die);
		pthread_mutex_unlock(philo->left_fork);
		return (NULL);
	}
	while (1)
	{
		if (check_death(philo))
			return (NULL);
		philo_eat(philo);
		print_state(philo, " is sleeping");
		ft_sleep(philo->time_to_sleep);
		print_state(philo, " is thinking");
	}
	return (NULL);
}
