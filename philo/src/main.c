/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:04:22 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/20 16:40:58 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <string.h>

static bool	check_argv(char **argv);
static void	join_philosophers(t_table *table);
static bool	create_philosophers(t_table *table);
static bool	create_monitoring(pthread_t *thread, t_table *table);

int	main(int argc, char **argv)
{
	t_table		table;
	pthread_t	monitoring;

	memset(&table, 0, sizeof(t_table));
	if (!check_argv(argv) || (argc != 5 && argc != 6))
	{
		error_message(INFO_USAGE, ERROR_INVALID_USAGE, NULL);
		return (EXIT_FAILURE);
	}
	if (!parse_argv(argv, &table))
	{
		error_message(INFO_WRONG_VALUE, INFO_PHILO_NUMBER, ERROR_PHILONUMBER);
		return (EXIT_FAILURE);
	}
	if (!init_table(&table) || !create_philosophers(&table)
		|| !create_monitoring(&monitoring, &table))
	{
		clean_table(&table);
		return (EXIT_FAILURE);
	}
	join_philosophers(&table);
	pthread_join(monitoring, NULL);
	clean_table(&table);
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
			set_simulation_state(1, table);
			error_message(ERROR_THREAD, NULL, NULL);
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
		set_simulation_state(1, table);
		error_message(ERROR_THREAD, NULL, NULL);
		join_philosophers(table);
		return (false);
	}
	return (true);
}

static void	join_philosophers(t_table *table)
{
	size_t	index;

	index = 0;
	while (index < table->philo_number)
	{
		pthread_join(table->philos[index].thread, NULL);
		index++;
	}
}

static bool	check_argv(char **argv)
{
	size_t	index;
	char	*str;

	index = 1;
	while (argv[index])
	{
		str = argv[index];
		while (*str)
		{
			if (*str < '0' || *str > '9')
				return (false);
			str++;
		}
		index++;
	}
	return (true);
}
