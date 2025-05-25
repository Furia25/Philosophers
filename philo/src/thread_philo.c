/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 19:08:06 by val               #+#    #+#             */
/*   Updated: 2025/05/25 05:31:14 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	put_forks(t_philo *philo);
static void	take_forks(t_philo *philo);

void	*philo_routine(void *philo_p)
{
	t_philo	*self;

	self = (t_philo *)philo_p;
	while (!get_simulation_state(self->table))
	{
		philo_log(PHILO_LOG_THINKING, self);
		take_forks(self);
		philo_log(PHILO_LOG_EATING, self);
		pthread_mutex_lock(&self->data_mutex);
		self->last_meal = get_time_ms();
		self->meals_eaten += 1;
		pthread_mutex_unlock(&self->data_mutex);
		usleep(self->table->time_to_eat * 1000);
		put_forks(self);
		philo_log(PHILO_LOG_SLEEPING, self);
		usleep(self->table->time_to_sleep * 1000);
	}
	return (NULL);
}

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
		pthread_mutex_lock(&philo->right_neighbour->fork.mutex);
	else
		pthread_mutex_lock(&philo->fork.mutex);
	philo_log(PHILO_LOG_FORK, philo);
	if (philo->id % 2 == 0)
		pthread_mutex_lock(&philo->fork.mutex);
	else
		pthread_mutex_lock(&philo->right_neighbour->fork.mutex);
	philo_log(PHILO_LOG_FORK, philo);
}

static void	put_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->fork.mutex);
		pthread_mutex_unlock(&philo->right_neighbour->fork.mutex);
	}
	else
	{
		pthread_mutex_unlock(&philo->right_neighbour->fork.mutex);
		pthread_mutex_unlock(&philo->fork.mutex);
	}
}
