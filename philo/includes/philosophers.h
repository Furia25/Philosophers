/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:33:26 by vdurand           #+#    #+#             */
/*   Updated: 2025/05/24 19:10:47 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stddef.h>
# include <sys/time.h>
# include <stdint.h>

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	bool			taken;
}	t_fork;

typedef struct s_table	t_table;
typedef struct s_philo	t_philo;

struct s_philo
{
	pthread_t	thread;
	t_table		*table;
	t_philo		*right_neighbour;
	t_philo		*left_neighbour;
	t_fork		fork;
	size_t		id;
	size_t		meals_eaten;
	size_t		last_meal;
};

/*Main struct representing the table (The program)*/
struct s_table
{
	bool			initialized;
	t_philo			*philosophers;
	int				simulation_state;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	state_mutex;
	size_t			number_of_meal;
	size_t			philo_number;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	uint64_t		start_time;
};

size_t		ft_strlen(const char *str);
void		parse_argv(char **argv, t_table *table);
int			ft_atoi(const char *nptr);
void		ft_putstr_fd(char *s, int fd);
void		warning_message(char *message, char *message2, char *message3);
void		error_message(char *error, char *message, char *message2);

void		clean_table(t_table *table);
bool		init_table(t_table *table);
uint64_t	get_time_ms(void);

void		*philo_routine(void *);
void		*monitoring_routine(void *);

#endif