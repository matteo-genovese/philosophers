/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 21:53:29 by mgenoves          #+#    #+#             */
/*   Updated: 2025/02/16 17:27:53 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

int	check_data(t_data *data)
{
	if (data->num_philo < 1 || data->num_philo > 200)
	{
		printf("Error: number of philosophers must be between 1 and 200\n");
		return (1);
	}
	if (data->time_to_die < 0 || data->time_to_eat < 0
		|| data->time_to_sleep < 0)
	{
		printf("Error: time arguments must be positive integers\n");
		return (1);
	}
	if (data->num_eat_cycles == 0)
	{
		data->simulation_status = 0;
		return (0);
	}
	return (0);
}

int	check_args(int argc, char **argv, t_data *data)
{
	if (argc < 5 || argc > 6)
		return (printf("Error: wrong number of arguments\n"));
	if (!ft_is_string_digits(argv[1]) || !ft_is_string_digits(argv[2])
		|| !ft_is_string_digits(argv[3]) || !ft_is_string_digits(argv[4]))
		return (printf("Error: arguments must be positive integers\n"));
	data->num_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		if (!ft_is_string_digits(argv[5]))
			return (printf("Error: arguments must be positive integers\n"));
		data->num_eat_cycles = ft_atoi(argv[5]);
	}
	else
		data->num_eat_cycles = -1;
	return (check_data(data));
}
