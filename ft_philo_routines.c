/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_routines.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 12:02:20 by shkaruna          #+#    #+#             */
/*   Updated: 2024/12/30 17:06:33 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void philo_action_log(char *msg, t_philo *philo, int unlock)
{
    char *timestamp;

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
    (void)unlock;
    /*
    if (unlock)
    {
        pthread_mutex_unlock(&philo->simulation->logging_lock);
    }
    else
    {
        // Ensure we unlock if not specified to unlock
        pthread_mutex_unlock(&philo->simulation->logging_lock);
    }
    */
}
static int check_all_ate(t_philo *philos)
{
    int i;
    int finished;
    t_simulation *simulation;

    simulation = philos[0].simulation;
    if (simulation->max_meals == -1) // Unlimited meals
        return (0); // Do not stop the simulation

    i = 0;
    finished = 0;
    while (i < simulation->num_of_philos)
    {
        pthread_mutex_lock(&philos[i].simulation->meals_lock);
        if (philos[i].times_eaten >= simulation->max_meals)
            finished++;
        pthread_mutex_unlock(&philos[i].simulation->meals_lock);
        i++;
    }
    if (finished == simulation->num_of_philos)
    {
        simulation->meals_ate = 1;
        return (1);
    }
    return (0);
}

void check_philo_death(t_simulation *simulation, t_philo *philo)
{
    int i;

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
            break;
        if (simulation->max_meals != -1 && check_all_ate(philo)) // Only check meals if max_meals is set
            break;
    }
}
static void take_forks(t_philo *philo)
{
    // Lock forks first to maintain a consistent lock order
    pthread_mutex_lock(&philo->simulation->forks_mutex[philo->left_fork]);
    //philo_action_log("has taken a fork", philo, UNLOCK);
    pthread_mutex_lock(&philo->simulation->forks_mutex[philo->right_fork]);
    //philo_action_log("has taken a fork", philo, UNLOCK);
}

static void release_forks(t_philo *philo)
{
    // Release forks
    pthread_mutex_unlock(&philo->simulation->forks_mutex[philo->left_fork]);
    pthread_mutex_unlock(&philo->simulation->forks_mutex[philo->right_fork]);
}

void ft_eating(t_philo *philo)
{
    take_forks(philo);

    // Lock meals_lock after forks_mutex
    pthread_mutex_lock(&philo->simulation->meals_lock);

    // Allow indefinite eating if max_meals is -1
    if (philo->simulation->max_meals != -1 && philo->times_eaten >= philo->simulation->max_meals)
    {
        release_forks(philo);
        pthread_mutex_unlock(&philo->simulation->meals_lock);
        return; // Exit if max meals reached
    }

    // Update eating state
    philo_action_log("is eating", philo, UNLOCK);
    philo->last_ate = get_time();
    philo->times_eaten++;
    pthread_mutex_unlock(&philo->simulation->meals_lock);

    // Simulate eating time
    updated_sleep(philo->simulation->time_to_eat, philo->simulation);

    release_forks(philo);
}





