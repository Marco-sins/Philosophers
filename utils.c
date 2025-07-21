/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 12:42:09 by marco             #+#    #+#             */
/*   Updated: 2025/07/21 22:12:58 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_print_action(t_philo *philo, char *action)
{
    printf("Philosopher %d, %s\n", philo->id, action);
}

void    ft_usleep(long time, t_data *data)
{
    long start;

    start = ft_get_time();
    while (ft_stop(data))
    {
        if ((ft_get_time() - start) < time)
            break ;
        usleep((time * 1000) / 20);
    }
}

long    ft_get_time()
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int ft_threads(t_data *data)
{
    int i;
    pthread_t   *threads;

    i = 0;
    threads = malloc(sizeof(pthread_t) * (data->settings.num_philos + 1));
    if (!threads)
        return (FALSE);
    while (i < data->settings.num_philos)
    {
        if (pthread_create(&threads[i], NULL, philo_routine, &data->philos[i]))
            return (free(threads), FALSE);
        data->philos_created++;
        i++;
    }
    if (pthread_create(&threads[i], NULL, ft_monitor, data))
        return (free(threads), FALSE);
    data->monitor->thread_created++;
    i = 0;
    while (i < data->settings.num_philos + 1)
        pthread_join(threads[i++], NULL);
    return (ft_destroy_threads(threads, data), TRUE);
}
