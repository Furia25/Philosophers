/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:26:09 by vdurand           #+#    #+#             */
/*   Updated: 2025/05/26 17:19:06 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	clamp_with_warning(int *value, int min,
				char *message, char *message2);

bool	parse_argv(char **argv, t_table *table)
{
	int	temp;

	temp = ft_atoi(argv[1]);
	if (temp == 0)
		return (false);
	table->philo_number = temp;
	temp = ft_atoi(argv[2]);
	clamp_with_warning(&temp, 1, INFO_TIME_DIE, WARNING_VALUE);
	table->time_to_die = temp;
	temp = ft_atoi(argv[3]);
	clamp_with_warning(&temp, 1, INFO_TIME_EAT, WARNING_VALUE);
	table->time_to_eat = temp;
	temp = ft_atoi(argv[4]);
	clamp_with_warning(&temp, 1, INFO_TIME_SLEEP, WARNING_VALUE);
	table->time_to_sleep = temp;
	table->number_of_meal = -1;
	if (!argv[5])
		return (true);
	temp = ft_atoi(argv[5]);
	if (temp == 0)
		warning_message(WARNING_MEALSNULL, NULL, NULL);
	table->number_of_meal = temp;
	return (true);
}

static void	clamp_with_warning(int *value, int min,
	char *message, char *message2)
{
	if (*value < min)
	{
		*value = min;
		warning_message(INFO_WRONG_VALUE, message, message2);
	}
}
