/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmembril <mmembril@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 20:04:41 by marco             #+#    #+#             */
/*   Updated: 2025/07/23 17:25:42 by mmembril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	if (data)
	{
		while (i < data->forks_created)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		if (!data->print_mutex_created)
			pthread_mutex_destroy(&data->print_mutex);
		if (!data->meal_check_created)
			pthread_mutex_destroy(&data->meal_check);
	}
}

static void	ft_free_structs(t_data *data)
{
	if (data)
	{
		if (data->philos)
			free(data->philos);
		if (data->forks)
			free(data->forks);
		if (data->monitor)
			free(data->monitor);
		free(data);
	}
}

void	ft_free_all(t_data *data)
{
	ft_destroy_mutex(data);
	ft_free_structs(data);
}
