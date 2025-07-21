/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 21:02:07 by marco             #+#    #+#             */
/*   Updated: 2025/07/21 22:03:56 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int  ft_init_philo(t_data *data)
{
    int i;

    i = 0;
    data->philos = (t_philo *)malloc(sizeof(t_philo) * data->settings.num_philos);
    if (!data->philos)
        return (FALSE);
    while (i < data->settings.num_philos)
    {
        data->philos[i].id = i + 1;
        data->philos[i].meals_eaten = 0;
        data->philos[i].last_meal_time = ft_get_time();
        data->philos[i].left_fork = &data->forks[i];
        data->philos[i].data = data;
        if (i < data->settings.num_philos - 1)
            data->philos[i].right_fork = &data->forks[i + 1];
        else
            data->philos[i].right_fork = &data->forks[0];
        i++;
    }
    return (TRUE);
}

static int ft_init_forks(t_data *data)
{
    int i;
    int res;

    data->forks = malloc(sizeof(pthread_mutex_t) * data->settings.num_philos);
    if (!data->forks)
        return (FALSE);
    i = 0;
    while (i < data->settings.num_philos)
    {
        res = pthread_mutex_init(&data->forks[i], NULL);
        if (res != 0)
            return (FALSE);
        data->forks_created++;
        i++;
    }
    return (TRUE);
}

static int ft_init_monitor(t_data *data)
{
    int res;

    data->monitor = malloc(sizeof(t_monitor));
    if (!data->monitor)
        return (FALSE);
    data->monitor->data = data;
    data->monitor->stop = 0;
    data->monitor->thread_created = 1;
    res = pthread_mutex_init(&data->monitor->stop_mutex, NULL);
    if (res != 0)
        return (FALSE);
    data->monitor->mutex_created = 1;
    res = pthread_mutex_init(&data->meal_check, NULL);
    if (res != 0)
        return (FALSE);
    data->meal_check_created = 1;
    return (TRUE);
}

t_data    *ft_init(int ac, char **av)
{
    t_data  *data;

    data = (t_data *)malloc(sizeof(t_data));
    if (!data)
        return (NULL);
    data->settings.num_philos = atoi(av[1]);
    data->settings.time_to_die = atoi(av[2]);
    data->settings.time_to_eat = atoi(av[3]);
    data->settings.time_to_sleep = atoi(av[4]);
    data->philos_created = 0;
    if (ac == 6)
        data->settings.max_meals = atoi(av[5]);
    else
        data->settings.max_meals = -1;
    if (!ft_init_forks(data) || !ft_init_philo(data) || !ft_init_monitor(data))
        return (printf("EEEEE"), NULL);
    return (data);
}
