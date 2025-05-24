/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_monitoring.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 19:08:18 by val               #+#    #+#             */
/*   Updated: 2025/05/24 19:20:59 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>

void	*monitoring_routine(void *)
{
	while (true)
	{
		usleep(1000);
		break;
	}
	return (NULL);
}
