/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmembril <mmembril@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 12:42:09 by marco             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/07/30 20:32:06 by marco            ###   ########.fr       */
=======
/*   Updated: 2025/07/30 19:03:48 by mmembril         ###   ########.fr       */
>>>>>>> 3511a57e033e488bf5ba03ed100212b7cbdd4fb6
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
<<<<<<< HEAD
	while (((ft_get_time() - start) < time) && !ft_stop(data))
		usleep(500);
=======
	(void)data;
	while ((ft_get_time() - start) < time)
		usleep(50);
>>>>>>> 3511a57e033e488bf5ba03ed100212b7cbdd4fb6
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
