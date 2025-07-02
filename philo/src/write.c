/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:31:53 by val               #+#    #+#             */
/*   Updated: 2025/07/02 16:06:26 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_log(char *message, t_philo *philo)
{
	uint64_t	elapsed;

	elapsed = get_time_ms() - philo->table->start_time;
	pthread_mutex_lock(&philo->table->write_mutex);
	if (!get_simulation_state(philo->table))
		printf("%lu %zu %s\n", elapsed, philo->id, message);
	pthread_mutex_unlock(&philo->table->write_mutex);
}

static void	system_message(char *message, char *message2, char *message3);

void	announce(char *message, char *message2, char *message3, t_table *table)
{
	pthread_mutex_lock(&table->write_mutex);
	ft_putstr_fd("\033[46m", 2);
	ft_putstr_fd("Announce:", 2);
	ft_putstr_fd("\033[0m", 2);
	ft_putstr_fd(" ", 2);
	system_message(message, message2, message3);
	pthread_mutex_unlock(&table->write_mutex);
}

void	warning_message(char *message, char *message2, char *message3)
{
	ft_putstr_fd("\033[33m", 2);
	ft_putstr_fd("Warning: ", 2);
	ft_putstr_fd("\033[0m", 2);
	system_message(message, message2, message3);
}

void	error_message(char *error, char *message, char *message2)
{
	ft_putstr_fd("\033[31m", 2);
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd("\033[0m", 2);
	system_message(error, message, message2);
}

static void	system_message(char *message, char *message2, char *message3)
{
	if (message)
		ft_putstr_fd(message, 2);
	if (message2)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(message2, 2);
	}
	if (message3)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(message3, 2);
	}
	ft_putstr_fd("\n", 2);
}
