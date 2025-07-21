/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:45:00 by marco             #+#    #+#             */
/*   Updated: 2025/07/20 17:29:11 by marco            ###   ########.fr       */
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

    i = 0;
    while (i < data->settings.num_philos)
    {
        pthread_mutex_lock(&data->meal_check);
        if (ft_get_time() - data->philos[i].last_meal_time > data->settings.time_to_die)
        {
            ft_print_action(&data->philos[i], "died");
            data->monitor->stop = 1;
            pthread_mutex_unlock(&data->meal_check);
            return (FALSE);
        }
        pthread_mutex_unlock(&data->meal_check);
        i++;
    }
    return (TRUE);
}

void    *ft_monitor(void *arg)
{
    t_data  *data;

    data = (t_data *)arg;
    while (data->monitor->stop)
    {
        if (!ft_is_philo_dead(data))
            return (NULL);
        if (data->settings.max_meals != -1 && data->philo_eaten_max == data->settings.num_philos)
        {
            data->monitor->stop = 1;
            return (NULL);
        }
    }
    return (NULL);
}
