/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 12:12:30 by shkaruna          #+#    #+#             */
/*   Updated: 2024/12/30 21:27:12 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "philo_struct.h"

# define UNLOCK 1
# define LOCK 0

int				ft_atoi(const char *nptr);
int				ft_error_msg(char *msg);
void			*ft_routine(void *args);
void			ft_end_dining(t_simulation *simulation);
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
int				ft_valid_input(t_simulation *simulation, int argc,
					char *argv[]);

#endif