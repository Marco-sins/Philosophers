/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 20:04:41 by marco             #+#    #+#             */
/*   Updated: 2025/07/21 21:32:42 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void    ft_destroy_mutex(t_data *data)
{
    int i;

    i = 0;
    while (i < data->forks_created)
    {
        pthread_mutex_destroy(&data->forks[i]);
        i++;
    }
    if (!data->print_mutex_created)
        pthread_mutex_destroy(&data->print_mutex);
    if (!data->meal_check_created)
        pthread_mutex_destroy(&data->meal_check);
    if (!data->monitor->mutex_created)
        pthread_mutex_destroy(&data->monitor->stop_mutex);
}

void    ft_destroy_threads(pthread_t *threads, t_data *data)
{
    int i;
    
    i = 0;
    if (!data->monitor->thread_created)
        pthread_detach(threads[i++]);
    while (i < data->philos_created)
        pthread_detach(threads[i++]);
}

static void ft_free_structs(t_data *data)
{
    if (data->philos)
        free(data->philos);
    if (data->forks)
        free(data->forks);
    if (data->monitor)
        free(data->monitor);
    if (data)
        free(data);
}

void    ft_free_all(t_data *data)
{
    ft_destroy_mutex(data);
    ft_free_structs(data);
}