/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:45:00 by marco             #+#    #+#             */
/*   Updated: 2025/07/22 21:55:11 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_stop(t_data *data)
{
    int status;

    pthread_mutex_lock(&data->monitor->stop_mutex);
    status = data->monitor->stop;
    pthread_mutex_unlock(&data->monitor->stop_mutex);
    return (status);
}

static int  ft_is_philo_dead(t_data *data)
{
    int i;
    int b;

    i = 0;
    b = TRUE;
    while (i < data->settings.num_philos)
    {
        pthread_mutex_lock(&data->meal_check);
        if (data->settings.max_meals && data->philos[i].meals_eaten < data->settings.max_meals)
            b = FALSE;
        if (ft_get_time() - data->philos[i].last_meal_time > data->settings.time_to_die)
        {
            ft_print_action(&data->philos[i], "died");
            pthread_mutex_unlock(&data->meal_check);
            return (TRUE);
        }
        pthread_mutex_unlock(&data->meal_check);
        i++;
    }
    pthread_mutex_lock(&data->monitor->stop_mutex);
    if (data->settings.max_meals != -1 && b)
        data->monitor->stop = 1;
    pthread_mutex_unlock(&data->monitor->stop_mutex);
    return (FALSE);
}

void    *ft_monitor(void *arg)
{
    t_data  *data;

    data = (t_data *)arg;
    while (!ft_stop(data))
    {
        if (ft_is_philo_dead(data))
        {
            pthread_mutex_lock(&data->monitor->stop_mutex);
            data->monitor->stop = 1;
            pthread_mutex_unlock(&data->monitor->stop_mutex);
            return (NULL);
        }
    }
    return (NULL);
}
