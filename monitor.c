/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmembril <mmembril@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:45:00 by marco             #+#    #+#             */
/*   Updated: 2025/07/30 19:22:16 by mmembril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_stop(t_data *data)
{
	int	status;

	pthread_mutex_lock(&data->monitor->stop_mutex);
	status = data->monitor->stop;
	pthread_mutex_unlock(&data->monitor->stop_mutex);
	return (status);
}

static int	ft_check_philos(t_data *data, int i, int *b)
{
	pthread_mutex_lock(&data->meal_check);
	if (data->philos[i].meals_eaten < data->settings.max_meals)
		*b = FALSE;
	if (ft_get_time()
		- data->philos[i].last_meal_time > data->settings.time_to_die)
	{
		pthread_mutex_unlock(&data->meal_check);
		ft_print_action(&data->philos[i], "died", ft_get_time());
		return (TRUE);
	}
	pthread_mutex_unlock(&data->meal_check);
	return (FALSE);
}

static int	ft_is_philo_dead(t_data *data)
{
	int	i;
	int	b;

	i = 0;
	b = TRUE;
	while (i < data->settings.num_philos)
	{
		if (ft_check_philos(data, i, &b))
			return (TRUE);
		i++;
	}
	pthread_mutex_lock(&data->monitor->stop_mutex);
	if (data->settings.max_meals != -1 && b)
		data->monitor->stop = 1;
	pthread_mutex_unlock(&data->monitor->stop_mutex);
	return (FALSE);
}

void	*ft_monitor(void *arg)
{
	t_data	*data;

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
		ft_usleep(100, data);
	}
	return (NULL);
}
