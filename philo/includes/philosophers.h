/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:33:26 by vdurand           #+#    #+#             */
/*   Updated: 2025/05/09 17:31:48 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stddef.h>

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	bool			useable;
}	t_fork;

typedef struct s_philo	t_philo;

struct s_philo
{
	t_philo	*neighbour;
	t_fork	fork;
	size_t	id;
};

typedef	struct s_table
{
	t_philo			*philosophers;
	pthread_mutex_t	write_mutex;
	size_t			philo_number;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
}	t_table;

size_t	ft_strlen(const char *str);
void	parse_argv(char **argv, t_table *table);
int		ft_atoi(const char *nptr);
void	ft_putstr_fd(char *s, int fd);
#endif