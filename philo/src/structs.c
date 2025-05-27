/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:44:28 by val               #+#    #+#             */
/*   Updated: 2025/05/26 22:17:38 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <string.h>

void	clean_table(t_table *table)
{
	size_t	index;

	if (table->initialized)
	{
		pthread_mutex_destroy(&table->write_mutex);
		pthread_mutex_destroy(&table->state_mutex);
		index = 0;
		while (index < table->philo_number)
		{
			pthread_mutex_destroy(&table->philos[index].fork.mutex);
			pthread_mutex_destroy(&table->philos[index].data_mutex);
			index++;
		}
	}
	free(table->philos);
}

static bool	init_mutex(t_table *table);
static bool	init_philosophers(t_table *table);

bool	init_table(t_table *table)
{
	if (get_time_ms() == 0)
		return (false);
	table->even = table->philo_number % 2 == 0;
	table->simulation_state = 0;
	if (!init_mutex(table))
	{
		error_message(ERROR_MUTEX, NULL, NULL);
		return (false);
	}
	table->philos = malloc(sizeof(t_philo) * table->philo_number);
	if (!table->philos)
	{
		error_message(ERROR_MEMORY, NULL, NULL);
		return (false);
	}
	memset(table->philos, 0, sizeof(t_philo) * table->philo_number);
	table->start_time = get_time_ms() + (table->philo_number * 5);
	if (!init_philosophers(table))
	{
		error_message(ERROR_MUTEX, NULL, NULL);
		return (false);
	}
	table->initialized = true;
	return (true);
}

static bool	init_mutex(t_table *table)
{
	if (pthread_mutex_init(&table->state_mutex, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&table->write_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&table->state_mutex);
		return (false);
	}
	return (true);
}

static bool	init_philosopher(size_t i, t_philo *philo, t_table *table);

static bool	init_philosophers(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->philo_number)
	{
		if (!init_philosopher(i, &table->philos[i], table))
			break ;
		i++;
	}
	if (i == table->philo_number)
		return (true);
	while (i-- > 0)
	{
		pthread_mutex_destroy(&table->philos[i].fork.mutex);
		pthread_mutex_destroy(&table->philos[i].data_mutex);
	}
	return (false);
}

static bool	init_philosopher(size_t i, t_philo *philo, t_table *table)
{
	philo->id = i + 1;
	philo->table = table;
	philo->last_meal = table->start_time;
	philo->right_neighbour = \
		&table->philos[(i + 1) % table->philo_number];
	if (pthread_mutex_init(&philo->fork.mutex, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&philo->data_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&philo->fork.mutex);
		return (false);
	}
	return (true);
}
