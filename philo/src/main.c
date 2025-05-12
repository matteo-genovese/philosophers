/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 19:41:12 by mgenoves          #+#    #+#             */
/*   Updated: 2025/02/28 11:29:39 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_all(t_philo *philo, int num_philo)
{
	int	i;

	if (!philo)
		return ;
	pthread_mutex_lock(&philo->data->simulation_status_mutex);
	philo->data->simulation_status = 0;
	pthread_mutex_unlock(&philo->data->simulation_status_mutex);
	usleep(1000);
	i = -1;
	while (++i < num_philo)
	{
		pthread_mutex_destroy(&philo[i].meals_mutex);
		pthread_mutex_unlock(philo[i].left_fork);
		if (philo[i].left_fork)
		{
			pthread_mutex_destroy(philo[i].left_fork);
			free(philo[i].left_fork);
		}
		pthread_mutex_destroy(&philo[i].meal_time_mutex);
	}
	pthread_mutex_destroy(&philo->data->print_mutex);
	pthread_mutex_destroy(&philo->data->philo_finished_mutex);
	pthread_mutex_destroy(&philo->data->simulation_status_mutex);
	pthread_mutex_destroy(&philo->data->forks_status_mutex);
	free(philo);
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	while_main(t_philo *philo, t_data *data, int ret)
{
	int	i;

	i = -1;
	while (++i < data->num_philo)
	{
		ret = pthread_create(&philo[i].thread, NULL, philo_routine, &philo[i]);
		if (ret)
		{
			printf("Error: pthread_create() returned %d\n", ret);
			free_all(philo, data->num_philo);
			return (1);
		}
	}
	i = -1;
	while (++i < data->num_philo)
	{
		ret = pthread_join(philo[i].thread, NULL);
		if (ret != 0)
		{
			printf("Error joining thread %d\n", i);
			free_all(philo, data->num_philo);
			return (1);
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;
	int		ret;

	if (start_main(&data, argc, argv))
		return (1);
	philo = malloc(sizeof(t_philo) * data.num_philo);
	if (!philo)
		return (1);
	if (init_philo(philo, &data))
		return (1);
	ret = 0;
	if (while_main(philo, &data, ret))
		return (1);
	free_all(philo, data.num_philo);
	return (0);
}
