/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 12:00:41 by shkaruna          #+#    #+#             */
/*   Updated: 2024/12/30 17:09:23 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

static int ft_init_mutex(t_simulation *simulation)
{
    int i;

    i = 0;
    // Initialize forks mutexes
    while (i < simulation->num_of_philos)
    {
        if (pthread_mutex_init(&(simulation->forks_mutex[i]), NULL))
        {
            return (1); // Return error if mutex initialization fails
        }
        i++;
    }

    // Initialize meals and logging mutexes
    if (pthread_mutex_init(&simulation->meals_lock, NULL))
    {
        return (1);
    }
    if (pthread_mutex_init(&simulation->logging_lock, NULL))
    {
        return (1);
    }
    if (pthread_mutex_init(&simulation->state_lock, NULL))
    {
        return (1);
    }

    return (0); // Success
}

static int	ft_init_philo(t_simulation *simulation)
{
	int	i;

	i = 0;
	while (i < simulation->num_of_philos)
	{
		simulation->philos[i].times_eaten = 0;
		simulation->philos[i].index = i + 1;
		simulation->philos[i].index_str = ft_itoa(i + 1);
		if (!simulation->philos[i].index_str)
			break ;
		simulation->philos[i].left_fork = i;
		simulation->philos[i].right_fork = (i + 1) % simulation->num_of_philos;
		simulation->philos[i].simulation = simulation;
		i++;
	}
	if (i != simulation->num_of_philos)
	{
		while (i >= 0)
		{
			free(simulation->philos[i].index_str);
			i--;
		}
		return (1);
	}
	return (0);
}

int	ft_init(t_simulation *simulation)
{
	simulation->philos = malloc(sizeof(t_philo) * simulation->num_of_philos);
	if (!simulation->philos)
		return (0);
	simulation->forks_mutex = malloc(sizeof(pthread_mutex_t) * simulation->num_of_philos);
	if (!simulation->forks_mutex)
	{
		free(simulation->philos);
		return (0);
	}
	if (ft_init_mutex(simulation))
	{
		free(simulation->philos);
		free(simulation->forks_mutex);
		return (0);
	}
	if (ft_init_philo(simulation))
	{
		free(simulation->philos);
		free(simulation->forks_mutex);
		return (0);
	}
	return (1);
}
