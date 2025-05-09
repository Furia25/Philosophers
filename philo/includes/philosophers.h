/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:33:26 by vdurand           #+#    #+#             */
/*   Updated: 2025/05/09 16:51:53 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include "libft.h"
# include <pthread.h>

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	bool			useable;
}	t_fork;

typedef struct s_philo
{
	t_philo	*neighbour;
	t_fork	fork;
}	t_philo;

typedef	struct s_table
{
	t_philo			*philosophers;
	pthread_mutex_t	write_mutex;
}	t_table;

#endif