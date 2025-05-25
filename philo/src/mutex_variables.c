/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_variables.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 02:33:23 by val               #+#    #+#             */
/*   Updated: 2025/05/25 03:42:59 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

inline bool	get_simulation_state(t_table *table)
{
	bool	result;

	pthread_mutex_lock(&table->state_mutex);
	result = table->simulation_state;
	pthread_mutex_unlock(&table->state_mutex);
	return (result)	;
}

inline void	set_simulation_state(bool value, t_table *table)
{
	pthread_mutex_lock(&table->state_mutex);
	table->simulation_state = value;
	pthread_mutex_unlock(&table->state_mutex);
}
