/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 21:22:36 by shkaruna          #+#    #+#             */
/*   Updated: 2024/12/30 21:48:42 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_STRUCT_H
# define PHILO_STRUCT_H

# include "philo.h"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

struct	s_simulation;

typedef struct s_philo
{
	int					times_eaten;
	int					index;
	char				*index_str;
	int					left_fork;
	int					right_fork;
	unsigned long		last_ate;
	struct s_simulation	*simulation;
	pthread_t			thread_id;
}						t_philo;

typedef struct s_simulation
{
	int					num_of_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					max_meals;
	unsigned long		start_time;
	int					stop_simulation;
	int					meals_ate;
	t_philo				*philos;
	pthread_mutex_t		*forks_mutex;
	pthread_mutex_t		meals_lock;
	pthread_mutex_t		logging_lock;
	pthread_mutex_t		state_lock;
}						t_simulation;

#endif