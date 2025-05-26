/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 19:08:06 by val               #+#    #+#             */
/*   Updated: 2025/05/26 17:09:20 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	put_forks(t_philo *philo);
static bool	take_forks(t_philo *philo);
static void	update_meals(t_philo *self);

void	*philo_routine(void *philo_p)
{
	t_philo		*self;

	self = (t_philo *)philo_p;
	time_wait_to(self->table->start_time);
	if (self->id % 2 == 0)
		usleep(10000);
	while (!get_simulation_state(self->table))
	{
		philo_log(PHILO_LOG_THINKING, self);
		if (!self->table->even)
			sleep_check(self->table->time_to_eat, self->table);
		if (!take_forks(self))
			return (NULL);
		update_meals(self);
		philo_log(PHILO_LOG_EATING, self);
		if (!sleep_check(self->table->time_to_eat, self->table))
			return (NULL);
		put_forks(self);
		philo_log(PHILO_LOG_SLEEPING, self);
		if (!sleep_check(self->table->time_to_sleep, self->table))
			return (NULL);
	}
	return (NULL);
}

static void	update_meals(t_philo *self)
{
	pthread_mutex_lock(&self->data_mutex);
	self->last_meal = get_time_ms();
	self->meals_eaten += 1;
	pthread_mutex_unlock(&self->data_mutex);
}

static bool	take_fork(t_philo *philo, t_fork *fork)
{
	while (true)
	{
		if (get_simulation_state(philo->table))
			return (false);
		pthread_mutex_lock(&fork->mutex);
		if (!fork->taken)
		{
			philo_log(PHILO_LOG_FORK, philo);
			fork->taken = 1;
			pthread_mutex_unlock(&fork->mutex);
			break ;
		}
		pthread_mutex_unlock(&fork->mutex);
		usleep(500);
	}
	return (true);
}

static bool	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (!take_fork(philo, &philo->right_neighbour->fork))
			return (false);
		return (take_fork(philo, &philo->fork));
	}
	else
	{
		if (!take_fork(philo, &philo->fork))
			return (false);
		return (take_fork(philo, &philo->right_neighbour->fork));
	}
}

static void	put_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork.mutex);
		philo->fork.taken = 0;
		pthread_mutex_unlock(&philo->fork.mutex);
		pthread_mutex_lock(&philo->right_neighbour->fork.mutex);
		philo->right_neighbour->fork.taken = 0;
		pthread_mutex_unlock(&philo->right_neighbour->fork.mutex);
	}
	else
	{
		pthread_mutex_lock(&philo->right_neighbour->fork.mutex);
		philo->right_neighbour->fork.taken = 0;
		pthread_mutex_unlock(&philo->right_neighbour->fork.mutex);
		pthread_mutex_lock(&philo->fork.mutex);
		philo->fork.taken = 0;
		pthread_mutex_unlock(&philo->fork.mutex);
	}
}
