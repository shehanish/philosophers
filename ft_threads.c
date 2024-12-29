/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threads.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 12:25:58 by shkaruna          #+#    #+#             */
/*   Updated: 2024/12/29 21:33:34 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	*ft_routine(void *args)
{
	t_philo			*philo;
	t_simulation	*simulation;

	philo = (t_philo *)args;
	simulation = philo->simulation;
	if (philo->index % 2 && simulation->num_of_philos > 1)
		updated_sleep(simulation->time_to_eat / 50, simulation);
	while (!simulation->stop_simulation && !simulation->meals_ate)
	{
		ft_eating(philo);
		philo_action_log("is sleeping", philo, UNLOCK);
		updated_sleep(simulation->time_to_sleep, simulation);
		philo_action_log("is thinking", philo, UNLOCK);
	}
	return (NULL);
}
void	ft_end_dining(t_simulation *simulation)
{
	int	i;

	i = 0;
	while (i < simulation->num_of_philos)
	{
		if (simulation->num_of_philos == 1)
			pthread_detach(simulation->philos[i].thread_id);
		else
			pthread_join(simulation->philos[i].thread_id, NULL);
		i++;
	}
	i = 0;
	while (i < simulation->num_of_philos)
	{
		pthread_mutex_destroy(&simulation->forks_mutex[i]);
		i++;
	}
	pthread_mutex_destroy(&simulation->meals_lock);
	pthread_mutex_destroy(&simulation->logging_lock);
	i = 0;
	while (i < simulation->num_of_philos)
	{
		free(simulation->philos[i].index_str);
		i++;
	}
}
// int	ft_begin_dining(t_simulation *simulation)
// {
//     int	i;
//     pthread_t monitor_thread;

//     i = -1;
//     simulation->start_time = get_time();
//     while (++i < simulation->num_of_philos)
//     {
//         simulation->philos[i].last_ate = get_time();
//         if (pthread_create(&simulation->philos[i].thread_id,
//                 NULL, ft_routine, &(simulation->philos[i])))
//             return (0);
//     }

//     if (pthread_create(&monitor_thread, NULL, monitor, simulation->philos))
//         return (0);

//     pthread_join(monitor_thread, NULL);

//     ft_end_dining(simulation);
//     return (1);
// }
int	ft_begin_dining(t_simulation *simulation)
{
	int	i;

	i = -1;
	simulation->start_time = get_time();
	while (++i < simulation->num_of_philos)
	{
		simulation->philos[i].last_ate = get_time();
		if (pthread_create(&simulation->philos[i].thread_id,
				NULL, ft_routine, &(simulation->philos[i])))
			return (0);
	}
	
	check_philo_death(simulation, simulation->philos);
	ft_end_dining(simulation);
	return (1);
}
