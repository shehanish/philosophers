/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routines_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 12:02:20 by shkaruna          #+#    #+#             */
/*   Updated: 2024/12/30 21:42:22 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_check_all_eat(t_philo *philos)
{
	t_simulation	*simulation;
	int				i;
	int				finished;

	simulation = philos[0].simulation;
	i = 0;
	finished = 0;
	while (i < simulation->num_of_philos)
	{
		pthread_mutex_lock(&simulation->meals_lock);
		if (philos[i].times_eaten >= simulation->max_meals)
			finished++;
		pthread_mutex_unlock(&simulation->meals_lock);
		i++;
	}
	pthread_mutex_lock(&simulation->state_lock);
	if (finished == simulation->num_of_philos)
	{
		simulation->meals_ate = 1;
		pthread_mutex_unlock(&simulation->state_lock);
		return (1);
	}
	pthread_mutex_unlock(&simulation->state_lock);
	return (0);
}

static int	check_simulation_status(t_simulation *simulation, t_philo *philo)
{
	pthread_mutex_lock(&simulation->state_lock);
	if (simulation->stop_simulation)
	{
		pthread_mutex_unlock(&simulation->state_lock);
		return (1);
	}
	pthread_mutex_unlock(&simulation->state_lock);
	if (simulation->max_meals != -1 && ft_check_all_eat(philo))
	{
		return (1);
	}
	return (0);
}

static int	check_philo_death_check(t_simulation *simulation, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < simulation->num_of_philos)
	{
		pthread_mutex_lock(&simulation->meals_lock);
		if ((int)(get_time() - philo[i].last_ate) >= simulation->time_to_die)
		{
			philo_action_log("died", &philo[i], LOCK);
			pthread_mutex_lock(&simulation->state_lock);
			simulation->stop_simulation = 1;
			pthread_mutex_unlock(&simulation->state_lock);
			pthread_mutex_unlock(&simulation->meals_lock);
			return (1);
		}
		pthread_mutex_unlock(&simulation->meals_lock);
		i++;
	}
	return (0);
}

void	check_philo_death(t_simulation *simulation, t_philo *philo)
{
	int	should_break;

	while (1)
	{
		should_break = check_simulation_status(simulation, philo);
		if (should_break)
			break ;
		should_break = check_philo_death_check(simulation, philo);
		if (should_break)
			break ;
	}
}

void	philo_action_log(char *msg, t_philo *philo, int unlock)
{
	char	*timestamp;

	(void)unlock;
	pthread_mutex_lock(&philo->simulation->logging_lock);
	timestamp = ft_itoa(get_time() - philo->simulation->start_time);
	pthread_mutex_lock(&philo->simulation->state_lock);
	if (!philo->simulation->stop_simulation && !philo->simulation->meals_ate)
	{
		write(STDOUT_FILENO, timestamp, strlen(timestamp));
		write(STDOUT_FILENO, " ", 1);
		write(STDOUT_FILENO, philo->index_str, strlen(philo->index_str));
		write(STDOUT_FILENO, " ", 1);
		write(STDOUT_FILENO, msg, strlen(msg));
		write(STDOUT_FILENO, "\n", 1);
	}
	pthread_mutex_unlock(&philo->simulation->state_lock);
	free(timestamp);
	pthread_mutex_unlock(&philo->simulation->logging_lock);
}
