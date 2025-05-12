/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:45:07 by mgenoves          #+#    #+#             */
/*   Updated: 2025/02/28 12:07:04 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

void	thinking(t_philo *philo)
{
	int	status;

	pthread_mutex_lock(&philo->data->simulation_status_mutex);
	status = philo->data->simulation_status;
	pthread_mutex_unlock(&philo->data->simulation_status_mutex);
	if (!status)
		return ;
	print_status(philo, "is thinking");
}

void	take_forks(t_philo *philo)
{
	int	left_idx;
	int	right_idx;
	int	status;

	pthread_mutex_lock(&philo->data->simulation_status_mutex);
	status = philo->data->simulation_status;
	pthread_mutex_unlock(&philo->data->simulation_status_mutex);
	if (!status)
		return ;
	left_idx = philo->id - 1;
	right_idx = philo->id % philo->data->num_philo;
	while (status && !check_death(philo))
	{
		if (take_right_fork(philo, right_idx))
			break ;
		usleep(100);
	}
	while (status && !check_death(philo))
	{
		if (take_left_fork(philo, left_idx, right_idx))
			break ;
		usleep(100);
	}
}

void	eating(t_philo *philo)
{
	int	status;

	pthread_mutex_lock(&philo->data->simulation_status_mutex);
	status = philo->data->simulation_status;
	pthread_mutex_unlock(&philo->data->simulation_status_mutex);
	if (!status)
		return ;
	pthread_mutex_lock(&philo->meals_mutex);
	print_status(philo, "is eating");
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meals_mutex);
	pthread_mutex_lock(&philo->meal_time_mutex);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->meal_time_mutex);
	usleep(philo->data->time_to_eat * 1000);
}

void	sleeping(t_philo *philo)
{
	int			status;
	long long	current_time;
	long long	sleep_end_time;
	long long	remaining_sleep;

	pthread_mutex_lock(&philo->data->simulation_status_mutex);
	status = philo->data->simulation_status;
	pthread_mutex_unlock(&philo->data->simulation_status_mutex);
	if (!status)
		return ;
	print_status(philo, "is sleeping");
	sleep_end_time = get_time() + philo->data->time_to_sleep;
	while (1)
	{
		if (check_death(philo))
			return ;
		current_time = get_time();
		if (current_time >= sleep_end_time)
			break ;
		remaining_sleep = sleep_end_time - current_time;
		if (remaining_sleep > 10)
			usleep(10 * 1000);
		else
			usleep(remaining_sleep * 1000);
	}
}

void	leave_forks(t_philo *philo)
{
	int	left_idx;
	int	right_idx;

	left_idx = philo->id - 1;
	right_idx = philo->id % philo->data->num_philo;
	pthread_mutex_lock(&philo->data->forks_status_mutex);
	philo->data->forks_status[left_idx] = 0;
	philo->data->forks_status[right_idx] = 0;
	pthread_mutex_unlock(&philo->data->forks_status_mutex);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
