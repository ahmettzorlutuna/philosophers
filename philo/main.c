/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azorlutu <azorlutu@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:49:50 by azorlutu          #+#    #+#             */
/*   Updated: 2025/03/27 12:49:51 by azorlutu         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

int	main(int argc, char **argv)
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	t_data			data;
	int				number;

	if (check_args(argc, argv) != 0)
		return (2);
	number = ft_atoi(argv[1]);
	philos = malloc(sizeof(t_philo) * number);
	forks = malloc(sizeof(pthread_mutex_t) * number);
	if (!philos || !forks)
	{
		error_message("Malloc error\n", ERR_MALLOC);
		return (1);
	}
	if (init_philo_datas(philos, forks, &data, argv) != 0)
		return (3);
	if (init_mutexes(philos, &data, argv) != 0)
		return (4);
	if (start_simuation(philos, &data, argv) != 0)
		return (5);
	ft_free(philos, forks, &data);
	return (0);
}
