/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 21:48:04 by mgenoves          #+#    #+#             */
/*   Updated: 2025/02/28 12:15:36 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "./checks.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	int				num_philo;
	long long		time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_eat_cycles;
	pthread_mutex_t	print_mutex;
	int				simulation_status;
	pthread_mutex_t	simulation_status_mutex;
	int				philo_finished;
	pthread_mutex_t	philo_finished_mutex;
	int				*forks_status;
	pthread_mutex_t	forks_status_mutex;
	long long		start_time;
}	t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				meals_eaten;
	long long		last_meal_time;
	pthread_mutex_t	meal_time_mutex;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meals_mutex;
	struct s_data	*data;
}	t_philo;

int			init_philo(t_philo *philo, t_data *data);
void		*philo_routine(void *arg);

void		thinking(t_philo *philo);
void		take_forks(t_philo *philo);
void		eating(t_philo *philo);
void		sleeping(t_philo *philo);
void		leave_forks(t_philo *philo);

int			check_fork_available(t_philo *philo, int fork_idx);
int			take_right_fork(t_philo *philo, int right_idx);
int			take_left_fork(t_philo *philo, int left_idx, int right_idx);
int			should_exit_simulation(t_philo *philo);
int			handle_eating_cycle(t_philo *philo);
int			handle_post_eating(t_philo *philo);

int			check_death(t_philo *philo);
int			check_meals(t_philo *philo);

long long	get_time(void);
void		print_status(t_philo *philo, char *status);

int			start_main(t_data *data, int argc, char **argv);

#endif
