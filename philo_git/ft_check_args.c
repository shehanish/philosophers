/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 11:59:24 by shkaruna          #+#    #+#             */
/*   Updated: 2024/12/28 18:54:44 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"


int	ft_valid_input(t_simulation *simulation, int argc, char *argv[])
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!ft_is_int(argv[i]))
			return (0);
		if (ft_atoi(argv[i]) < 0)
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
		simulation->max_meals = 0;
	if (simulation->num_of_philos < 1 || simulation->time_to_die < 0 || simulation->time_to_eat < 0
		|| simulation->time_to_sleep < 0 || simulation->max_meals < 0)
		return (0);
	return (1);
}