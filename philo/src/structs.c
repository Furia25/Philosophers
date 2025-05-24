/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:44:28 by val               #+#    #+#             */
/*   Updated: 2025/05/24 19:24:37 by val              ###   ########.fr       */
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
			pthread_mutex_destroy(&table->philosophers[index].fork.mutex);
			index++;
		}
	}
	free(table->philosophers);
}

static bool	init_mutex(t_table *table);
static bool	init_philosophers(t_table *table);

bool	init_table(t_table *table)
{
	table->simulation_state = 0;
	if (!init_mutex(table))
	{
		error_message("Failed to create mutex", NULL, NULL);
		return (false);
	}
	table->philosophers = malloc(sizeof(t_philo) * table->philo_number);
	if (!table->philosophers)
	{
		error_message("Failed to allocate memory", NULL, NULL);
		return (false);
	}
	memset(table->philosophers, 0, sizeof(t_philo) * table->philo_number);
	if (!init_philosophers(table))
	{
		error_message("Failed to create mutex", NULL, NULL);
		return (false);
	}
	table->start_time = get_time_ms();
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

static bool	init_philosophers(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->philo_number)
	{
		table->philosophers[i].id = i;
		table->philosophers[i].table = table;
		table->philosophers[i].left_neighbour = &table->philosophers[\
			(i + table->philo_number - 1) % table->philo_number];
		table->philosophers[i].right_neighbour = &table->philosophers[\
			(i + 1) % table->philo_number];
		if (pthread_mutex_init(&table->philosophers[i].fork.mutex, NULL) != 0)
		{
			while (i-- > 0)
				pthread_mutex_destroy(&table->philosophers[i].fork.mutex);
			return (false);
		}
		i++;
	}
	return (true);
}
