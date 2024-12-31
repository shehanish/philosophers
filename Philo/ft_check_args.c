/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 11:59:24 by shkaruna          #+#    #+#             */
/*   Updated: 2024/12/30 21:31:24 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_is_valid_number(char *str)
{
	if (!ft_is_int(str) || ft_atoi(str) < 0)
		return (0);
	return (1);
}

int	ft_valid_input(t_simulation *simulation, int argc, char *argv[])
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!ft_is_valid_number(argv[i]))
			return (0);
		i++;
	}
	simulation->num_of_philos = ft_atoi(argv[1]);
	simulation->time_to_die = ft_atoi(argv[2]);
	simulation->time_to_eat = ft_atoi(argv[3]);
	simulation->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		simulation->max_meals = ft_atoi(argv[5]);
	else
		simulation->max_meals = -1;
	if (simulation->num_of_philos < 1 || simulation->time_to_die < 0
		|| simulation->time_to_eat < 0 || simulation->time_to_sleep < 0
		|| simulation->max_meals < -1)
		return (0);
	return (1);
}
