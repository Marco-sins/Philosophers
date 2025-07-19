/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 20:04:41 by marco             #+#    #+#             */
/*   Updated: 2025/07/19 21:36:20 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_destroy_mutex(t_data *data, int j)
{
    int i;

    i = 0;
    while (i < j)
    {
        pthread_mutex_destroy(&data->forks[i]);
        i++;
    }
}

void    ft_destroy_threads(t_data *data, int j)
{
    int i;
    
    i = 0;
    while (i < j)
    {
        pthread_detach(&data->philos[i].thread);
        i++;
    }
}