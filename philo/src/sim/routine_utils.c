/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:14:30 by mgenoves          #+#    #+#             */
/*   Updated: 2025/02/28 12:14:43 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

int	should_exit_simulation(t_philo *philo)
{
	int	status;

	pthread_mutex_lock(&philo->data->simulation_status_mutex);
	status = philo->data->simulation_status;
	pthread_mutex_unlock(&philo->data->simulation_status_mutex);
	return (!status || check_death(philo) || check_meals(philo));
}

int	handle_eating_cycle(t_philo *philo)
{
	int	status;

	take_forks(philo);
	pthread_mutex_lock(&philo->data->simulation_status_mutex);
	status = philo->data->simulation_status;
	pthread_mutex_unlock(&philo->data->simulation_status_mutex);
	if (!status || check_death(philo))
	{
		leave_forks(philo);
		return (0);
	}
	eating(philo);
	leave_forks(philo);
	return (1);
}

int	handle_post_eating(t_philo *philo)
{
	int	status;

	if (check_meals(philo))
		return (0);
	sleeping(philo);
	pthread_mutex_lock(&philo->data->simulation_status_mutex);
	status = philo->data->simulation_status;
	pthread_mutex_unlock(&philo->data->simulation_status_mutex);
	if (!status || check_death(philo))
		return (0);
	thinking(philo);
	return (1);
}
