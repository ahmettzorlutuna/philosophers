/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azorlutu <azorlutu@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:32:16 by azorlutu          #+#    #+#             */
/*   Updated: 2025/04/06 15:32:17 by azorlutu         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_simuation(t_philo *philos, t_data *data, char **argv)
{
	int	i;
	int	philos_number;

	philos_number = ft_atoi(argv[1]);
	i = -1;
	while (++i < philos_number)
	{
		if (pthread_create(&philos[i].thread, NULL,
				&philosophers_routine, &philos[i]) != 0)
			error_message("Thread creation failed", ERR_THREAD);
		usleep(100);
	}
	if (pthread_create(&data->monitor_thread, NULL,
			&monitor_routine, philos) != 0)
		error_message("Thread creation failed", ERR_THREAD);
	i = -1;
	while (++i < philos_number)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
			error_message("Thread join failed", ERR_THREAD);
	}
	if (pthread_join(data->monitor_thread, NULL) != 0)
		error_message("Thread join failed", ERR_THREAD);
	return (0);
}
