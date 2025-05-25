/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:33:26 by vdurand           #+#    #+#             */
/*   Updated: 2025/05/25 04:57:01 by val              ###   ########.fr       */
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
# include <stdatomic.h>
# include <unistd.h>
# include <stdio.h>

# define PHILO_LOG_FORK	"has taken a fork"
# define PHILO_LOG_THINKING	"is thinking"
# define PHILO_LOG_EATING	"is eating"
# define PHILO_LOG_SLEEPING	"is sleeping"
# define PHILO_LOG_DIED	"died"

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	bool			taken;
}	t_fork;

typedef struct s_table	t_table;
typedef struct s_philo	t_philo;

struct s_philo
{
	size_t			id;
	pthread_t		thread;
	t_philo			*right_neighbour;
	t_philo			*left_neighbour;
	t_fork			fork;
	pthread_mutex_t	data_mutex;
	long			meals_eaten;
	uint64_t		last_meal;
	int				fork_in_hands;
	t_table			*table;
};

/*Main struct representing the table (The program)*/
struct s_table
{
	bool			initialized;
	t_philo			*philos;
	int				simulation_state;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	state_mutex;
	long			number_of_meal;
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

void		*philo_routine(void *philo_p);
void		*monitoring_routine(void *table_p);

void		philo_log(char *message, t_philo *philo);

bool		get_simulation_state(t_table *table);
void		set_simulation_state(bool value, t_table *table);

#endif