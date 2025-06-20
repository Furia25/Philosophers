/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:33:26 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/20 16:40:46 by vdurand          ###   ########.fr       */
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
# include <unistd.h>
# include <stdio.h>

# define PHILO_LOG_FORK	"has taken a fork"
# define PHILO_LOG_THINKING	"is thinking"
# define PHILO_LOG_EATING	"is eating"
# define PHILO_LOG_SLEEPING	"is sleeping"
# define PHILO_LOG_DIED	"died"

# define ANNOUNCE_EATEN	"All philosophers ate all required meals"
# define ANNOUNCE_TIME	"Simulation has reached max simulation time"

# define INFO_PHILO_NUMBER	"Philo's number"
# define INFO_TIME_DIE	"Time to die"
# define INFO_TIME_EAT	"Time to eat"
# define INFO_TIME_SLEEP	"Time to sleep"
# define INFO_WRONG_VALUE	"Wrong value"
# define INFO_USAGE	"Invalid usage"

# define ERROR_MEMORY	"Failed to allocate memory"
# define ERROR_MUTEX	"Failed to create mutex"
# define ERROR_THREAD	"Failed to create thread"
# define ERROR_PHILONUMBER	"has to be a least one"
# define ERROR_INVALID_USAGE	"<int : philo_number> <int : time_to_die> \
<int : time_to_eat> \
<int : time_to_sleep> [int : number_of_meal]"

# define WARNING_VALUE	"value has been set to one"
# define WARNING_MEALSNULL	"Number of meals of 0, \
means the simulation will stop instantly"

# define SIMULATION_TIME	-1

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
	t_fork			fork;
	pthread_mutex_t	data_mutex;
	long			meals_eaten;
	uint64_t		last_meal;
	int				fork_in_hands;
	t_table			*table;
};

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
	bool			even;
};

size_t		ft_strlen(const char *str);
bool		parse_argv(char **argv, t_table *table);
int			ft_atoi(const char *nptr);
void		ft_putstr_fd(char *s, int fd);
void		announce(char *message, char *message2,
				char *message3, t_table *table);
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

void		time_wait_to(uint64_t start_time);
int			sleep_check(size_t milliseconds, t_table *table);

#endif