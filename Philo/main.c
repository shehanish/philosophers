/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 12:05:03 by shkaruna          #+#    #+#             */
/*   Updated: 2024/12/29 14:21:18 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_simulation	simulation;

	if (argc < 5 || argc > 6)
		return (ft_error_msg("Not enough/ too much arguments!\n"));
	simulation.meals_ate = 0;
	simulation.stop_simulation = 0;
	if (!ft_valid_input(&simulation, argc, argv))
		return (ft_error_msg("Invalid input.\n"));
	if (!ft_init(&simulation))
		return (ft_error_msg("Init failed.\n"));
	if (!ft_begin_dining(&simulation))
		return (ft_error_msg("Threads failed.\n"));
	return (0);
}
