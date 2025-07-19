/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 21:02:07 by marco             #+#    #+#             */
/*   Updated: 2025/07/19 21:39:46 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void ft_init_philo(t_data *data)
{
    int i;

    i = 0;
    data->philos = (t_philo *)malloc(sizeof(t_philo) * data->settings.num_philos);
    if (!data->philos)
        return ;
    while (i < data->settings.num_philos)
    {
        data->philos[i].id = i + 1;
        data->philos[i].meals_eaten = 0;
        data->philos[i].last_meal_time = 0;
        data->philos[i].left_fork = &data->forks[i];
        if (i < data->settings.num_philos - 1)
            data->philos[i].right_fork = &data->forks[i + 1];
        else
            data->philos[i].right_fork = &data->forks[0];
        i++;
    }
}

static void ft_init_fork(t_data *data)
{
    int i;
    int j;
    int res;

    data->forks = malloc(sizeof(pthread_mutex_t) * data->settings.num_philos);
    if (!data->forks)
        return ;
    i = 0;
    while (i < data->settings.num_philos)
    {
        res = pthread_mutex_init(&data->forks[i], NULL);
        if (res != 0)
            break ;
        i++;
    }
    j = 0;
    if (i < data->settings.num_philos)
    {
        while (j < i)
        {
            pthread_mutex_destroy(&data->forks[j]);
            j++;
        }
        free(data->forks);
    }
}

void    go_threads(t_data *data)
{
    int i;
    int j;
    int res;

    i = 0;
    while (i < data->settings.num_philos)
    {
        res = pthread_create(&data->philos->thread, NULL, philo_routine, &data->philos[i]);
        if (res != 0)
            break ;
        i++;
    }
    if (i < data->settings.num_philos)
    {
        ft_destroy_threads(data, i);
    }
    res = pthread_create(&data->checker, NULL, philo_routine, &data);
    if (res != 0)
    {
        ft_destroy_threads(data, 5);
        pthread_detach(data->checker);
    }
}


t_data    *ft_init(t_data *data, int ac, char **av)
{
    data = (t_data *)malloc(sizeof(t_data));
    if (!data)
        return (NULL);
    data->settings.num_philos = atoi(av[1]);
    data->settings.time_to_die = atoi(av[2]);
    data->settings.time_to_eat = atoi(av[3]);
    data->settings.time_to_sleep = atoi(av[4]);
    if (av[5])
        data->settings.max_meals = atoi(av[5]);
    else
        data->settings.max_meals = NULL;
    ft_init_forks(data);
    if (!data->forks)
        return (NULL);
    ft_init_philo(data);
    if (!data->philos)
        return (ft_destroy_mutex(data), NULL);
    return (data);
}