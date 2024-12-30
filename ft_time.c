/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 12:59:28 by shkaruna          #+#    #+#             */
/*   Updated: 2024/12/30 17:56:12 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (unsigned long)1000) + (time.tv_usec / 1000));
}

void	updated_sleep(unsigned long duration, t_simulation *simulation)
{
	unsigned long	start;

	start = get_time();
	while (1)
	{
		pthread_mutex_lock(&simulation->state_lock);
		if (simulation->stop_simulation)
		{
			pthread_mutex_unlock(&simulation->state_lock);
			break ;
		}
		pthread_mutex_unlock(&simulation->state_lock);
		if (get_time() - start >= duration)
			break ;
		usleep(simulation->num_of_philos * 2);
	}
}


int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
