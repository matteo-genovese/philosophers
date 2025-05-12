/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 23:15:44 by mgenoves          #+#    #+#             */
/*   Updated: 2025/02/28 10:43:25 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

int	start_main(t_data *data, int argc, char **argv)
{
	if (check_args(argc, argv, data))
		return (1);
	if (data->num_philo == 1)
	{
		printf("0 1 has taken a fork\n");
		usleep(data->time_to_die * 1000);
		printf("%lld 1 died\n", data->time_to_die);
		return (1);
	}
	if (data->num_eat_cycles == 0)
	{
		printf("All philosophers have eaten 0 times\n");
		return (1);
	}
	return (0);
}

int	init_while(t_philo *philo, int i, t_data *data)
{
	philo[i].id = i + 1;
	philo[i].meals_eaten = 0;
	philo[i].last_meal_time = get_time();
	philo[i].data = data;
	if (pthread_mutex_init(&philo[i].meals_mutex, NULL))
		return (printf("Error: mutex initialization failed\n"));
	if (pthread_mutex_init(&philo[i].meal_time_mutex, NULL))
		return (printf("Error: mutex initialization failed\n"));
	philo[i].left_fork = malloc(sizeof(pthread_mutex_t));
	if (!philo[i].left_fork)
	{
		printf("Error: malloc failed\n");
		return (1);
	}
	if (pthread_mutex_init(philo[i].left_fork, NULL))
	{
		printf("Error: mutex initialization failed\n");
		free(philo[i].left_fork);
		return (1);
	}
	return (0);
}

int	init_philo(t_philo *philo, t_data *data)
{
	int	i;

	data->philo_finished = 0;
	data->simulation_status = 1;
	data->start_time = get_time();
	if (pthread_mutex_init(&data->philo_finished_mutex, NULL)
		|| pthread_mutex_init(&data->print_mutex, NULL)
		|| pthread_mutex_init(&data->simulation_status_mutex, NULL))
		return (1);
	data->forks_status = malloc(sizeof(int) * data->num_philo);
	if (!data->forks_status)
		return (1);
	i = -1;
	while (++i < data->num_philo)
		data->forks_status[i] = 0;
	if (pthread_mutex_init(&data->forks_status_mutex, NULL))
		return (1);
	i = -1;
	while (++i < data->num_philo)
		init_while(philo, i, data);
	i = -1;
	while (++i < data->num_philo)
		philo[i].right_fork = philo[(i + 1) % data->num_philo].left_fork;
	return (0);
}
