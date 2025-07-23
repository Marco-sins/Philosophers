/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmembril <mmembril@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 19:34:45 by marco             #+#    #+#             */
/*   Updated: 2025/07/23 16:42:27 by mmembril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 5 && ac != 6)
		return (printf("ERROR\n"), 1);
	data = ft_init(ac, av);
	if (!data)
		return (printf("ERROR\n"), ft_free_all(data), 1);
	if (data->settings.max_meals == 0)
		return (ft_free_all(data), 1);
	if (!ft_threads(data))
		return (ft_free_all(data), 1);
	ft_free_all(data);
	return (0);
}
