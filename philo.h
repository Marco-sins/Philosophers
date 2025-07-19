/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:25:59 by marco             #+#    #+#             */
/*   Updated: 2025/07/19 21:57:29 by marco            ###   ########.fr       */
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

typedef struct s_data
{
    t_philo        *philos;
    t_settings      settings;
    pthread_mutex_t *forks;
    pthread_mutex_t print_mutex;
    pthread_t       checker;
}    t_data;

typedef struct s_philo
{
    int             id;
    int             meals_eaten;
    long            last_meal_time;
    pthread_t       thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
}   t_philo;

typedef struct s_settings
{
    int             num_philos;
    int             time_to_eat;
    int             time_to_sleep;
    int             time_to_die;
    int             max_meals;
}   t_settings;

t_data    *ft_init(t_data *data, int ac, char **av);
void    ft_destroy_mutex(t_data *data);
void    ft_destroy_threads(t_data *data, int j);
void    go_threads(t_data *data);
void    philo_routine(void *arg);
void    monitor();

#endif