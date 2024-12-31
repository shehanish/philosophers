/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 21:35:11 by shkaruna          #+#    #+#             */
/*   Updated: 2024/12/30 21:35:56 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->simulation->forks_mutex[philo->left_fork]);
	philo_action_log("has taken a fork", philo, UNLOCK);
	pthread_mutex_lock(&philo->simulation->forks_mutex[philo->right_fork]);
	philo_action_log("has taken a fork", philo, UNLOCK);
}

static void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->simulation->forks_mutex[philo->left_fork]);
	pthread_mutex_unlock(&philo->simulation->forks_mutex[philo->right_fork]);
}

void	ft_eating(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->simulation->meals_lock);
	if (philo->simulation->max_meals != -1
		&& philo->times_eaten >= philo->simulation->max_meals)
	{
		pthread_mutex_unlock(&philo->simulation->meals_lock);
		release_forks(philo);
		return ;
	}
	philo_action_log("is eating", philo, UNLOCK);
	philo->last_ate = get_time();
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->simulation->meals_lock);
	updated_sleep(philo->simulation->time_to_eat, philo->simulation);
	release_forks(philo);
}
