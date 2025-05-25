/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:17:37 by val               #+#    #+#             */
/*   Updated: 2025/05/25 21:01:03 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

uint64_t	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((uint64_t)(tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	time_wait_to(uint64_t start_time)
{
	while (get_time_ms() < start_time)
		continue ;
}

int	sleep_check(size_t milliseconds, t_table *table)
{
	size_t	start;

	start = get_time_ms();
	while ((get_time_ms() - start) < milliseconds)
	{
		if (get_simulation_state(table))
			return (0);
		usleep(100);
	}
	return (1);
}
