/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 12:12:30 by shkaruna          #+#    #+#             */
/*   Updated: 2024/12/30 17:04:34 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>

# define UNLOCK 1
# define LOCK 0

struct	s_simulation;

typedef struct s_philo
{
	int				times_eaten;
	int				index;
	char			*index_str;
	int				left_fork;
	int				right_fork;
	unsigned long	last_ate;
	struct s_simulation	*simulation;
	pthread_t		thread_id;
}				t_philo;

typedef struct s_simulation
{
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	unsigned long	start_time;
	int				stop_simulation;
	int				meals_ate;
	t_philo			*philos;
	pthread_mutex_t	*forks_mutex;
	pthread_mutex_t	meals_lock;
	pthread_mutex_t	logging_lock;
	pthread_mutex_t	state_lock; // Added mutex for shared state
}				t_simulation;

int				ft_atoi(const char *nptr);
int				ft_error_msg(char *msg);
void	*ft_routine(void *args);
void	ft_end_dining(t_simulation *simulation);
int				ft_strlen(char *str);
char			*ft_itoa(int nbr);
int				ft_is_int(const char *nptr);
int				ft_init(t_simulation *simulation);
void			philo_action_log(char *msg, t_philo *philo, int unlock);
void			ft_eating(t_philo *philo);
void			check_philo_death(t_simulation *simulation, t_philo *philo);
int				ft_begin_dining(t_simulation *simulation);
unsigned long	get_time(void);
void			updated_sleep(unsigned long duration, t_simulation *simulation);
int	ft_valid_input(t_simulation *simulation, int argc, char *argv[]);
// int check_all_ate(t_philo *philos);
// void *monitor(void *arg);
// int check_if_any_died(t_philo *philos);
// int	this_philo_dead(t_philo *philo, size_t time_to_die);



#endif