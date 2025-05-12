/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 12:51:53 by mgenoves          #+#    #+#             */
/*   Updated: 2025/02/28 12:14:20 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

void	print_status(t_philo *philo, char *status)
{
	long long	time;

	pthread_mutex_lock(&philo->data->print_mutex);
	time = get_time() - philo->data->start_time;
	if (philo->data->simulation_status)
		printf("%lld %d %s\n", time, philo->id, status);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

int	check_death(t_philo *philo)
{
	long long	current_time;
	long long	last_meal;
	int			status;

	pthread_mutex_lock(&philo->data->simulation_status_mutex);
	status = philo->data->simulation_status;
	pthread_mutex_unlock(&philo->data->simulation_status_mutex);
	if (!status)
		return (1);
	pthread_mutex_lock(&philo->meal_time_mutex);
	last_meal = philo->last_meal_time;
	pthread_mutex_unlock(&philo->meal_time_mutex);
	current_time = get_time();
	if (current_time - last_meal > philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->simulation_status_mutex);
		if (philo->data->simulation_status)
		{
			print_status(philo, "died");
			philo->data->simulation_status = 0;
		}
		pthread_mutex_unlock(&philo->data->simulation_status_mutex);
		return (1);
	}
	return (0);
}

int	check_meals(t_philo *philo)
{
	if (philo->data->num_eat_cycles == -1)
		return (0);
	if (philo->meals_eaten >= philo->data->num_eat_cycles)
	{
		pthread_mutex_lock(&philo->data->philo_finished_mutex);
		philo->data->philo_finished++;
		pthread_mutex_unlock(&philo->data->philo_finished_mutex);
		return (1);
	}
	return (0);
}

void	philo_while(t_philo *philo)
{
	while (1)
	{
		if (should_exit_simulation(philo))
			break ;
		if (!handle_eating_cycle(philo))
			break ;
		if (!handle_post_eating(philo))
			break ;
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2)
	{
		print_status(philo, "is thinking");
		usleep(1000);
	}
	philo_while(philo);
	if (philo->data->num_philo == philo->data->philo_finished)
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("All philosophers have eaten %d times\n",
			philo->data->num_eat_cycles);
		pthread_mutex_unlock(&philo->data->print_mutex);
	}
	return (NULL);
}
