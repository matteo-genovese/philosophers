/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_forks_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:05:55 by mgenoves          #+#    #+#             */
/*   Updated: 2025/02/28 12:08:55 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

int	check_fork_available(t_philo *philo, int fork_idx)
{
	pthread_mutex_lock(&philo->data->forks_status_mutex);
	if (philo->data->forks_status[fork_idx] == 0)
	{
		philo->data->forks_status[fork_idx] = 1;
		pthread_mutex_unlock(&philo->data->forks_status_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->forks_status_mutex);
	return (0);
}

int	take_right_fork(t_philo *philo, int right_idx)
{
	if (check_fork_available(philo, right_idx))
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		return (1);
	}
	return (0);
}

int	take_left_fork(t_philo *philo, int left_idx, int right_idx)
{
	if (check_fork_available(philo, left_idx))
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		return (1);
	}
	if (check_death(philo))
	{
		pthread_mutex_lock(&philo->data->forks_status_mutex);
		philo->data->forks_status[right_idx] = 0;
		pthread_mutex_unlock(&philo->data->forks_status_mutex);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	return (0);
}
