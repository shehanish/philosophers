/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_routines.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 12:02:20 by shkaruna          #+#    #+#             */
/*   Updated: 2024/12/28 19:42:21 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void	philo_action_log(char *msg, t_philo *philo, int unlock)
{
	char	*timestamp;

	timestamp = ft_itoa(get_time() - philo->simulation->start_time);
	pthread_mutex_lock(&philo->simulation->logging_lock);
	if (!philo->simulation->stop_simulation && !philo->simulation->meals_ate)
		printf("%s %s %s\n", timestamp, philo->index_str, msg);
	if (unlock)
		pthread_mutex_unlock(&philo->simulation->logging_lock);
	free(timestamp);
}

void	ft_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->simulation->forks_mutex[philo->left_fork]);
	philo_action_log("has taken a fork", philo, UNLOCK);
	pthread_mutex_lock(&philo->simulation->forks_mutex[philo->right_fork]);
	philo_action_log("has taken a fork", philo, UNLOCK);
	pthread_mutex_lock(&philo->simulation->meals_lock);
	philo_action_log("is eating", philo, UNLOCK);
	philo->last_ate = get_time();
	pthread_mutex_unlock(&philo->simulation->meals_lock);
	updated_sleep(philo->simulation->time_to_eat, philo->simulation);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->simulation->forks_mutex[philo->right_fork]);
	pthread_mutex_unlock(&philo->simulation->forks_mutex[philo->left_fork]);
}

void	check_philo_death(t_simulation *simulation, t_philo *philo)
{
	int	i;

	while (!simulation->meals_ate)
	{
		i = -1;
		while (++i < simulation->num_of_philos && !simulation->stop_simulation)
		{
			pthread_mutex_lock(&simulation->meals_lock);
			if ((int)(get_time() - philo[i].last_ate) >= simulation->time_to_die)
			{
				philo_action_log("died", &philo[i], LOCK);
				simulation->stop_simulation = 1;
			}
			pthread_mutex_unlock(&simulation->meals_lock);
		}
		if (simulation->stop_simulation)
			break ;
		i = 0;
		while (simulation->max_meals && i < simulation->num_of_philos
			&& philo[i].times_eaten >= simulation->max_meals)
			i++;
		simulation->meals_ate = (i == simulation->num_of_philos);
	}
}
