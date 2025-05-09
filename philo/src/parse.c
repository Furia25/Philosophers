/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:26:09 by vdurand           #+#    #+#             */
/*   Updated: 2025/05/09 17:32:54 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	clamp_with_warning(int *value, int min, char *message);

void	parse_argv(char **argv, t_table *table)
{
	int		temp;

	temp = ft_atoi(argv[1]);
	clamp_with_warning(&temp, 1, "The number of philosophers has been set to one");
	table->philo_number = temp;
	temp = ft_atoi(argv[2]);
	clamp_with_warning(&temp, 1, "Time to die value has been set to one");
	table->time_to_die = temp;
	temp = ft_atoi(argv[3]);
	clamp_with_warning(&temp, 1, "Time to eat value has been set to one");
	table->time_to_eat = temp;
	temp = ft_atoi(argv[4]);
	clamp_with_warning(&temp, 1, "Time to sleep value has been set to one");
	table->time_to_sleep = temp;
}

static void	clamp_with_warning(int *value, int min, char *message)
{
	if (*value < min)
	{
		*value = min;
		ft_putstr_fd("Warning : ", 2);
		ft_putstr_fd(message, 2);
		ft_putstr_fd("\n", 2);
	}
}