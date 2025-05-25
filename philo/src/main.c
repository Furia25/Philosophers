/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:04:22 by vdurand           #+#    #+#             */
/*   Updated: 2025/05/25 05:20:11 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <string.h>

static void join_philosophers(t_table *table);
static bool	create_philosophers(t_table *table);
static bool	create_monitoring(pthread_t *thread, t_table *table);

int	main(int argc, char **argv)
{
	t_table		table;
	pthread_t	monitoring;

	memset(&table, 0, sizeof(t_table));
	if (argc != 5 && argc != 6)
	{
		error_message("Usage", "<philo_number> <time_to_die> \
<time_to_eat> <time_to_sleep> [number_of_meal]", NULL);
		return (EXIT_FAILURE);
	}
	parse_argv(argv, &table);
	if (!init_table(&table)
		|| !create_monitoring(&monitoring, &table)
		|| !create_philosophers(&table))
	{
		clean_table(&table);
		return (EXIT_FAILURE);
	}
	join_philosophers(&table);
	pthread_join(monitoring, NULL);
	clean_table(&table);
	printf("%d\n", table.simulation_state);
	return (EXIT_SUCCESS);
}

static bool	create_philosophers(t_table *table)
{
	size_t	index;

	index = 0;
	while (index < table->philo_number)
	{
		if (pthread_create(&table->philos[index].thread,
			NULL, &philo_routine, &table->philos[index]) != 0)
		{
			error_message("Failed to create thread", NULL, NULL);
			while (index-- > 0)
				pthread_join(table->philos[index].thread, NULL);
			return (false);
		}
		index++;
	}
	return (true);
}

static bool	create_monitoring(pthread_t *thread, t_table *table)
{
	if (pthread_create(thread, NULL, &monitoring_routine, table) != 0)
	{
		error_message("Failed to create thread", NULL, NULL);
		return (false);
	}
	return (true);
}

static void join_philosophers(t_table *table)
{
	size_t	index;

	index = 0;
	while (index < table->philo_number)
	{
		pthread_join(table->philos[index].thread, NULL);
		index++;
	}
}
