/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 19:34:45 by marco             #+#    #+#             */
/*   Updated: 2025/07/20 17:42:16 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
    t_data  *data;
    int i;

    if (ac != 5 && ac != 6)
        return (printf("ERROR\n"), 1);
    data = ft_init(ac, av);
    if (!data)
        return (printf("ERROR\n"), ft_free_all(data), 1);
    pthread_join(data->monitor->thread, NULL);   
    i = 0;
    while (i < data->settings.num_philos)
    {
        pthread_join(data->philos[i].thread, NULL);
        i++;
    }
    ft_free_all(data);
    return (0);
}
