/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:25:59 by marco             #+#    #+#             */
/*   Updated: 2025/07/21 22:03:49 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define TRUE 1
# define FALSE 0

typedef struct s_monitor t_monitor;
typedef struct s_philo t_philo; 

typedef struct s_settings
{
    int             num_philos;
    int             time_to_eat;
    int             time_to_sleep;
    int             time_to_die;
    int             max_meals;
}   t_settings;

typedef struct s_data
{
    t_philo        *philos;
    int             philos_created;
    t_settings      settings;
    pthread_mutex_t *forks;
    int             forks_created;
    pthread_mutex_t print_mutex;
    int             print_mutex_created;
    t_monitor       *monitor;
    pthread_mutex_t meal_check;
    int             meal_check_created;
    int             philo_eaten_max;
}    t_data;

typedef struct s_monitor
{
    t_data  *data;
    int stop;
    pthread_mutex_t stop_mutex;
    int mutex_created;
    int thread_created;
}   t_monitor;

typedef struct s_philo
{
    int             id;
    int             meals_eaten;
    long            last_meal_time;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    t_data          *data;
}   t_philo;

t_data    *ft_init(int ac, char **av);
void    ft_print_action(t_philo *philo, char *action);
void    ft_usleep(long time, t_data *data);
long    ft_get_time();
void    *philo_routine(void *arg);
void    *ft_monitor(void *arg);
int ft_stop(t_data *data);
void    ft_free_all(t_data *data);
int ft_threads(t_data *data);
void    ft_destroy_threads(pthread_t *threads, t_data *data);

#endif