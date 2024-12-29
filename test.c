// #include "philo.h"

// int	main(int argc, char **argv)
// {
// 	t_simulation	simulation;

// 	if (argc < 5 || argc > 6)
// 		return (ft_error_msg("Not enough arguments!\n"));
// 	simulation.meals_ate = 0;
// 	simulation.stop_simulation = 0;
// 	if (!ft_valid_input(&simulation, argc, argv))
// 		return (ft_error_msg("Invalid input.\n"));
// 	if (!ft_init(&simulation))
// 		return (ft_error_msg("Init failed.\n"));
// 	if (!ft_begin_dining(&simulation))
// 		return (ft_error_msg("Threads failed.\n"));
// 	return (0);
// }

// int	ft_valid_input(t_simulation *simulation, int argc, char *argv[])
// {
// 	int	i;

// 	i = 1;
// 	while (i < argc)
// 	{
// 		if (!ft_is_int(argv[i]))
// 			return (0);
// 		if (ft_atoi(argv[i]) < 0)
// 			return (0);
// 		i++;
// 	}
// 	simulation->num_of_philos = ft_atoi(argv[1]);
// 	simulation->time_to_die = ft_atoi(argv[2]);
// 	simulation->time_to_eat = ft_atoi(argv[3]);
// 	simulation->time_to_sleep = ft_atoi(argv[4]);
// 	if (argc == 6)
// 		simulation->max_meals = ft_atoi(argv[5]);
// 	else
// 		simulation->max_meals = 0;
// 	if (simulation->num_of_philos < 1 || simulation->time_to_die < 0 || simulation->time_to_eat < 0
// 		|| simulation->time_to_sleep < 0 || simulation->max_meals < 0)
// 		return (0);
// 	return (1);
// }


// # include "philo.h"

// static int	ft_init_mutex(t_simulation *simulation)
// {
// 	int	i;

// 	i = 0;
// 	while (i < simulation->num_of_philos)
// 	{
// 		if (pthread_mutex_init(&(simulation->forks_mutex[i]), NULL))
// 			return (1);
// 		i++;
// 	}
// 	if (pthread_mutex_init(&simulation->meals_lock, NULL))
// 		return (1);
// 	if (pthread_mutex_init(&simulation->logging_lock, NULL))
// 		return (1);
// 	return (0);
// }

// static int	ft_init_philo(t_simulation *simulation)
// {
// 	int	i;

// 	i = 0;
// 	while (i < simulation->num_of_philos)
// 	{
// 		simulation->philos[i].times_eaten = 0;
// 		simulation->philos[i].index = i + 1;
// 		simulation->philos[i].index_str = ft_itoa(i + 1);
// 		if (!simulation->philos[i].index_str)
// 			break ;
// 		simulation->philos[i].left_fork = i;
// 		simulation->philos[i].right_fork = (i + 1) % simulation->num_of_philos;
// 		simulation->philos[i].simulation = simulation;
// 		i++;
// 	}
// 	if (i != simulation->num_of_philos)
// 	{
// 		while (i >= 0)
// 		{
// 			free(simulation->philos[i].index_str);
// 			i--;
// 		}
// 		return (1);
// 	}
// 	return (0);
// }

// int	ft_init(t_simulation *simulation)
// {
// 	simulation->philos = malloc(sizeof(t_philo) * simulation->num_of_philos);
// 	if (!simulation->philos)
// 		return (0);
// 	simulation->forks_mutex = malloc(sizeof(pthread_mutex_t) * simulation->num_of_philos);
// 	if (!simulation->forks_mutex)
// 	{
// 		free(simulation->philos);
// 		return (0);
// 	}
// 	if (ft_init_mutex(simulation))
// 	{
// 		free(simulation->philos);
// 		free(simulation->forks_mutex);
// 		return (0);
// 	}
// 	if (ft_init_philo(simulation))
// 	{
// 		free(simulation->philos);
// 		free(simulation->forks_mutex);
// 		return (0);
// 	}
// 	return (1);
// }

// void	philo_action_log(char *msg, t_philo *philo, int unlock)
// {
// 	char	*timestamp;

// 	timestamp = ft_itoa(get_time() - philo->simulation->start_time);
// 	pthread_mutex_lock(&philo->simulation->logging_lock);
// 	if (!philo->simulation->stop_simulation && !philo->simulation->meals_ate)
// 		printf("%s %s %s\n", timestamp, philo->index_str, msg);
// 	if (unlock)
// 		pthread_mutex_unlock(&philo->simulation->logging_lock);
// 	free(timestamp);
// }

// void	ft_eating(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->simulation->forks_mutex[philo->left_fork]);
// 	philo_action_log("has taken a fork", philo, UNLOCK);
// 	pthread_mutex_lock(&philo->simulation->forks_mutex[philo->right_fork]);
// 	philo_action_log("has taken a fork", philo, UNLOCK);
// 	pthread_mutex_lock(&philo->simulation->meals_lock);
// 	philo_action_log("is eating", philo, UNLOCK);
// 	philo->last_ate = get_time();
// 	pthread_mutex_unlock(&philo->simulation->meals_lock);
// 	updated_sleep(philo->simulation->time_to_eat, philo->simulation);
// 	philo->times_eaten++;
// 	pthread_mutex_unlock(&philo->simulation->forks_mutex[philo->right_fork]);
// 	pthread_mutex_unlock(&philo->simulation->forks_mutex[philo->left_fork]);
// }

// void	check_philo_death(t_simulation *simulation, t_philo *philo)
// {
// 	int	i;

// 	while (!simulation->meals_ate)
// 	{
// 		i = -1;
// 		while (++i < simulation->num_of_philos && !simulation->stop_simulation)
// 		{
// 			pthread_mutex_lock(&simulation->meals_lock);
// 			if ((int)(get_time() - philo[i].last_ate) >= simulation->time_to_die)
// 			{
// 				philo_action_log("died", &philo[i], LOCK);
// 				simulation->stop_simulation = 1;
// 			}
// 			pthread_mutex_unlock(&simulation->meals_lock);
// 		}
// 		if (simulation->stop_simulation)
// 			break ;
// 		i = 0;
// 		while (simulation->max_meals && i < simulation->num_of_philos
// 			&& philo[i].times_eaten >= simulation->max_meals)
// 			i++;
// 		simulation->meals_ate = (i == simulation->num_of_philos);
// 	}
// }

// void	*ft_routine(void *args)
// {
// 	t_philo			*philo;
// 	t_simulation	*simulation;

// 	philo = (t_philo *)args;
// 	simulation = philo->simulation;
// 	if (philo->index % 2 && simulation->num_of_philos > 1)
// 		updated_sleep(simulation->time_to_eat / 50, simulation);
// 	while (!simulation->stop_simulation && !simulation->meals_ate)
// 	{
// 		ft_eating(philo);
// 		philo_action_log("is sleeping", philo, UNLOCK);
// 		updated_sleep(simulation->time_to_sleep, simulation);
// 		philo_action_log("is thinking", philo, UNLOCK);
// 	}
// 	return (NULL);
// }
// void	ft_end_dining(t_simulation *simulation)
// {
// 	int	i;

// 	i = 0;
// 	while (i < simulation->num_of_philos)
// 	{
// 		if (simulation->num_of_philos == 1)
// 			pthread_detach(simulation->philos[i].thread_id);
// 		else
// 			pthread_join(simulation->philos[i].thread_id, NULL);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < simulation->num_of_philos)
// 	{
// 		pthread_mutex_destroy(&simulation->forks_mutex[i]);
// 		i++;
// 	}
// 	pthread_mutex_destroy(&simulation->meals_lock);
// 	pthread_mutex_destroy(&simulation->logging_lock);
// 	i = 0;
// 	while (i < simulation->num_of_philos)
// 	{
// 		free(simulation->philos[i].index_str);
// 		i++;
// 	}
// }

// int	ft_begin_dining(t_simulation *simulation)
// {
// 	int	i;

// 	i = -1;
// 	simulation->start_time = get_time();
// 	while (++i < simulation->num_of_philos)
// 	{
// 		simulation->philos[i].last_ate = get_time();
// 		if (pthread_create(&simulation->philos[i].thread_id,
// 				NULL, ft_routine, &(simulation->philos[i])))
// 			return (0);
// 	}
// 	check_philo_death(simulation, simulation->philos);
// 	pthread_mutex_unlock(&simulation->logging_lock);
// 	ft_end_dining(simulation);
// 	return (1);
// }

// unsigned long	get_time(void)
// {
// 	struct timeval	time;

// 	gettimeofday(&time, NULL);
// 	return ((time.tv_sec * (unsigned long)1000) + (time.tv_usec / 1000));
// }

// void	updated_sleep(unsigned long duration, t_simulation *simulation)
// {
// 	unsigned long	start;

// 	start = get_time();
// 	while (!simulation->stop_simulation)
// 	{
// 		if (get_time() - start >= duration)
// 			break ;
// 		usleep(simulation->num_of_philos * 2);
// 	}
// }

// int	ft_strlen(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 		i++;
// 	return (i);
// }
// static int	ft_num_len(int n)
// {
// 	int	i;

// 	i = 0;
// 	if (n <= 0)
// 		i++;
// 	while (n != 0)
// 	{
// 		n /= 10;
// 		i++;
// 	}
// 	return (i);
// }

// static void	ft_rev_str(char *str)
// {
//     int		start;
//     int		finish;
//     char	swap;

//     start = 0;
//     finish = ft_strlen(str) - 1;
//     while (start < finish)
//     {
//         swap = str[start];
//         str[start] = str[finish];
//         str[finish] = swap;
//         start++;
//         finish--;
//     }
// }

// char	*ft_itoa(int num)
// {
//     char			*str;
//     int				len;
//     unsigned int	tmp_num;

//     len = 0;
//     str = malloc(sizeof(*str) * (ft_num_len(num) + 1));
//     if (!str)
//         return (NULL);
//     if (num < 0)
//         tmp_num = -1 * num;
//     else
//         tmp_num = num;
//     while (tmp_num != 0)
//     {
//         str[len++] = (tmp_num % 10) + '0';
//         tmp_num /= 10;
//     }
//     if (num == 0)
//         str[len++] = '0';
//     if (num < 0)
//         str[len++] = '-';
//     str[len] = '\0';
//     ft_rev_str(str);
//     return (str);
// }

// static int	ft_isdigit(int c)
// {
// 	if (c >= 48 && c <= 57)
// 		return (1);
// 	return (0);
// }
// int	ft_atoi(const char *str)
// {
//     int		index;
//     int		sign;
//     long	result;

//     index = 0;
//     result = 0;
//     sign = 1;
//     while ((str[index] == ' ' || (str[index] >= 9 && str[index] <= 13)))
//         index++;
//     if (str[index] == '-')
//         sign = -1;
//     if (str[index] == '-' || str[index] == '+')
//         index++;
//     while (str[index] != '\0' && ft_isdigit(str[index]))
//     {
//         if (result > 922337203685477580 || (result == 922337203685477580
//                 && ((!sign && str[index] - '0' > 7) || (sign && str[index] - '0' > 8))))
//             return (-1 * (sign == 1));
//         else
//             result = (result * 10) + str[index++] - '0';
//     }
//     return (result * sign);
// }

// int	ft_error_msg(char *msg)
// {
// 	if (msg && *msg)
// 		printf("%s", msg);
// 	return (1);
// }


// int	ft_is_int(const char *str)
// {
// 	long	number;
// 	int		sign;

// 	number = 0;
// 	sign = 1;
// 	while (*str == ' ' || (*str >= 9 && *str <= 13))
// 		str++;
// 	if (*str == '-' || *str == '+')
// 	{
// 		if (*str == '-')
// 			sign = -1;
// 		str++;
// 	}
// 	while (*str >= '0' && *str <= '9')
// 	{
// 		if (number > 214748364 || (number == 214748364 && ((*str - '0' > 7 && sign == 1) || (*str - '0' > 8 && sign == -1))))
// 			return (0);
// 		number = number * 10 + (*str - '0');
// 		str++;
// 	}
// 	return (1);
// }

// #ifndef PHILO_H
// # define PHILO_H

// # include <pthread.h>
// # include <stdio.h>
// # include <stdlib.h>
// # include <unistd.h>
// # include <sys/time.h>

// # define UNLOCK 1
// # define LOCK 0

// typedef struct	s_simulation;

// typedef struct s_philo
// {
// 	int				times_eaten;
// 	int				index;
// 	char			*index_str;
// 	int				left_fork;
// 	int				right_fork;
// 	unsigned long	last_ate;
// 	struct s_simulation	*simulation;
// 	pthread_t		thread_id;
// }				t_philo;

// typedef struct s_simulation
// {
// 	int				num_of_philos;
// 	int				time_to_die;
// 	int				time_to_eat;
// 	int				time_to_sleep;
// 	int				max_meals;
// 	unsigned long	start_time;
// 	int				stop_simulation;
// 	int				meals_ate;
// 	t_philo			*philos;
// 	pthread_mutex_t	*forks_mutex;
// 	pthread_mutex_t	meals_lock;
// 	pthread_mutex_t	logging_lock;
// }				t_simulation;

// int				ft_atoi(const char *nptr);
// int				ft_error_msg(char *msg);
// void	*ft_routine(void *args);
// void	ft_end_dining(t_simulation *simulation);
// int				ft_strlen(char *str);
// char			*ft_itoa(int nbr);
// int				ft_is_int(const char *nptr);
// int				ft_init(t_simulation *simulation);
// void			philo_action_log(char *msg, t_philo *philo, int unlock);
// void			ft_eating(t_philo *philo);
// void			check_philo_death(t_simulation *simulation, t_philo *philo);
// int				ft_begin_dining(t_simulation *simulation);
// unsigned long	get_time(void);
// void			updated_sleep(unsigned long duration, t_simulation *simulation);
// int	ft_valid_input(t_simulation *simulation, int argc, char *argv[]);

// #endif