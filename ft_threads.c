/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threads.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 12:25:58 by shkaruna          #+#    #+#             */
/*   Updated: 2024/12/30 18:13:33 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	*ft_routine(void *args)
{
	t_philo			*philo;
	t_simulation	*simulation;
	int				should_continue;

	philo = (t_philo *)args;
	simulation = philo->simulation;
	if (philo->index % 2 && simulation->num_of_philos > 1)
		updated_sleep(simulation->time_to_eat / 50, simulation);
	
	while (1)
	{
		pthread_mutex_lock(&simulation->state_lock);
		should_continue = (!simulation->stop_simulation && !simulation->meals_ate);
		pthread_mutex_unlock(&simulation->state_lock);
		
		if (!should_continue)
			break;
			
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
		//pthread_mutex_destroy(&simulation->forks_mutex[i]);
		i++;
	}
	pthread_mutex_destroy(&simulation->meals_lock);
	pthread_mutex_destroy(&simulation->logging_lock);
	pthread_mutex_destroy(&simulation->state_lock);
	i = 0;
	while (i < simulation->num_of_philos)
	{
		free(simulation->philos[i].index_str);
		i++;
	}
	//free(simulation->philos);
	free(simulation->forks_mutex);
}

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
