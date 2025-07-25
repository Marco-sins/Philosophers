/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 12:42:09 by marco             #+#    #+#             */
/*   Updated: 2025/07/24 11:02:16 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_action(t_philo *philo, char *action, long time)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!ft_stop(philo->data))
		printf("%lu %d %s\n", time - philo->data->time, philo->id, action);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	ft_usleep(long time, t_data *data)
{
	long	start;

	start = ft_get_time();
	while (!ft_stop(data))
	{
		if ((ft_get_time() - start) >= time)
			break ;
		usleep(50);
	}
}

long	ft_get_time(void)
{
	static struct timeval	start;
	struct timeval			tv;

	gettimeofday(&tv, NULL);
	if (!start.tv_sec && !start.tv_usec)
		start = tv;
	return (((tv.tv_sec - start.tv_sec) * 1000) + ((tv.tv_usec - start.tv_usec)
			/ 1000));
}

int	ft_threads(t_data *data)
{
	int			i;

	i = 0;
	data->threads = malloc(sizeof(pthread_t) * (data->settings.num_philos + 1));
	if (!data->threads)
		return (FALSE);
	while (i < data->settings.num_philos)
	{
		if (pthread_create(&data->threads[i], NULL, philo_routine,
				&data->philos[i]))
			return (free(data->threads), FALSE);
		data->philos_created++;
		i++;
	}
	if (pthread_create(&data->threads[i], NULL, ft_monitor, data))
		return (free(data->threads), FALSE);
	i = 0;
	while (i < data->settings.num_philos + 1)
	{
		pthread_join(data->threads[i], NULL);
		i++;
	}
	free(data->threads);
	return (TRUE);
}
