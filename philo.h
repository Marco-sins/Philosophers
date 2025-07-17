/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmembril <mmembril@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:02:29 by mmembril          #+#    #+#             */
/*   Updated: 2025/07/17 20:17:20 by mmembril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

# define MAX_PHILOSOPHERS 200
# define MAX_FORKS 200
# define MAX_TIME 2147483647
# define MIN_TIME 0
# define MAX_EAT 2147483647
# define MIN_EAT 0
# define MAX_SLEEP 2147483647
# define MIN_SLEEP 0

typedef struct s_philo
{
    int				id;
    int				eat_count;
    long long		last_eat_time;
    pthread_mutex_t	fork_mutex;
    pthread_mutex_t	*next_fork_mutex;
}	t_philo;    

typedef struct s_data
{
    int				num_philosophers;
    int				time_to_eat;
    int				time_to_sleep;
    int				time_to_die;
    int				max_eat_count;
    bool			all_philos_fed;
    long long		start_time;
    pthread_mutex_t	print_mutex;
    pthread_mutex_t	death_mutex;
    t_philo			*philosophers;
}	t_data;

void		init_philosophers(t_data *data);
void		*philosopher_routine(void *arg);
long long	get_current_time(void);
void		print_status(t_data *data, int id, const char *status);
bool		check_death(t_data *data, int id);
void		destroy_mutexes(t_data *data);
void		free_resources(t_data *data);
bool		parse_arguments(int argc, char **argv, t_data *data);
bool		validate_arguments(int argc, char **argv);
void		start_simulation(t_data *data);
void		join_threads(t_data *data);
void		*monitor_philosophers(void *arg);
void		*eat_sleep_think(void *arg);
void		*check_all_fed(void *arg);
void		*check_death_condition(void *arg);
void		*wait_for_philosophers(void *arg);
void		*wait_for_forks(void *arg);
void		*release_forks(void *arg);
void		*print_final_status(t_data *data);
void		*initialize_mutexes(t_data *data);
void		*destroy_philosophers(t_data *data);
void		*initialize_data(t_data *data);     