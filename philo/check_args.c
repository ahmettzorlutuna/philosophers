/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azorlutu <azorlutu@student.42istanbul      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 22:45:39 by azorlutu          #+#    #+#             */
/*   Updated: 2025/04/16 22:45:41 by azorlutu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "limits.h"

static	int	is_valid_number(const char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static	int	validate_argument(int index, int number, int argc)
{
	if (index == 1 && (number < 1 || number > PHILO_MAX_COUNT))
		return (error_message(
				"Philosopher count mustbe between 1 and PHILO_MAX_COUNT.\n",
				ERR_ARGS));
	else if (index == 2 && (number < 1 || number > INT_MAX))
		return (error_message(
				"time_to_die must be a positive integer.\n",
				ERR_ARGS));
	else if (index == 3 && (number < 1 || number > INT_MAX))
		return (error_message(
				"time_to_eat must be a positive integer.\n",
				ERR_ARGS));
	else if (index == 4 && (number < 1 || number > INT_MAX))
		return (error_message(
				"time_to_sleep must be a positive integer.\n",
				ERR_ARGS));
	else if (index == 5 && argc == 6 && (number < 1 || number > INT_MAX))
		return (error_message(
				"notep must be a positive integer.\n",
				ERR_ARGS));
	return (0);
}

int	check_args(int argc, char **argv)
{
	int	i;
	int	number;

	if (argc != 5 && argc != 6)
		return (error_message(
				"The num. of arg. must be bet. 5 and 6, inclds. the prg name\n",
				ERR_ARGS));
	i = 0;
	while (++i < argc)
	{
		if (!is_valid_number(argv[i]))
			return (error_message(
					"All arguments must be valid integers.\n",
					ERR_ARGS));
		number = ft_atoi(argv[i]);
		if (validate_argument(i, number, argc) != 0)
			return (1);
	}
	return (0);
}
