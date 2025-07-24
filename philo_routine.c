/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 21:52:15 by marco             #+#    #+#             */
/*   Updated: 2025/07/24 11:30:26 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_think(t_philo *philo)
{
	ft_print_action(philo, "is thinking", ft_get_time());
}

static void	ft_sleep(t_philo *philo)
{
	ft_print_action(philo, "is sleeping", ft_get_time());
	ft_usleep(philo->data->settings.time_to_sleep, philo->data);
}

static void	ft_eat(t_philo *philo)
{
	long	time;

	time = ft_get_time();
	ft_print_action(philo, "is eating", time);
	pthread_mutex_lock(&philo->data->meal_check);
	philo->meals_eaten++;
	philo->last_meal_time = time;
	pthread_mutex_unlock(&philo->data->meal_check);
	ft_usleep(philo->data->settings.time_to_eat, philo->data);
}

static void	ft_take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		ft_print_action(philo, "has taken a fork", ft_get_time());
		pthread_mutex_lock(philo->right_fork);
		ft_print_action(philo, "has taken a fork", ft_get_time());
		ft_eat(philo);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		ft_print_action(philo, "has taken a fork", ft_get_time());
		pthread_mutex_lock(philo->left_fork);
		ft_print_action(philo, "has taken a fork", ft_get_time());
		ft_eat(philo);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->settings.time_to_eat / 2, philo->data);
	while (!ft_stop(philo->data))
	{
		ft_think(philo);
		if (philo->data->settings.num_philos == 1)
		{
			pthread_mutex_lock(philo->left_fork);
			ft_print_action(philo, "has taken a fork", ft_get_time());
			ft_usleep(philo->data->settings.time_to_die, philo->data);
			if (!ft_stop(philo->data))
				return (NULL);
		}
		ft_take_fork(philo);
		ft_sleep(philo);
	}
	return (NULL);
}
