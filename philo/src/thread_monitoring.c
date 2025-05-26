/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_monitoring.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 19:08:18 by val               #+#    #+#             */
/*   Updated: 2025/05/26 17:07:23 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_philos(t_philo *philo, t_table *table);
static bool	quit_check_meals(int index, t_table *table);

void	*monitoring_routine(void *table_p)
{
	t_table	*table;
	size_t	index;
	int		check_result;

	table = (t_table *)table_p;
	time_wait_to(table->start_time);
	while (true)
	{
		index = 0;
		while (index < table->philo_number)
		{
			check_result = check_philos(&table->philos[index], table);
			if (check_result == 0)
				break ;
			if (check_result == 2)
				return (NULL);
			index++;
		}
		if (quit_check_meals(index, table))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

static bool	quit_check_meals(int index, t_table *table)
{
	if (table->number_of_meal > -1 && index == table->philo_number)
	{
		announce(ANNOUNCE_EATEN, NULL, NULL);
		set_simulation_state(true, table);
		return (true);
	}
	return (false);
}

static int	check_philos(t_philo *philo, t_table *table)
{
	uint64_t	actual_time;
	long		meals;
	uint64_t	last;

	pthread_mutex_lock(&philo->data_mutex);
	meals = philo->meals_eaten;
	last = philo->last_meal;
	pthread_mutex_unlock(&philo->data_mutex);
	actual_time = get_time_ms();
	if (actual_time - last > table->time_to_die)
	{
		philo_log(PHILO_LOG_DIED, philo);
		set_simulation_state(true, table);
		return (2);
	}
	if (SIMULATION_TIME > 0
		&& actual_time - table->start_time > SIMULATION_TIME)
	{
		announce(ANNOUNCE_TIME, NULL, NULL);
		set_simulation_state(true, table);
		return (2);
	}
	if (table->number_of_meal > -1 && meals < table->number_of_meal)
		return (0);
	return (1);
}
