/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 19:03:13 by shkaruna          #+#    #+#             */
/*   Updated: 2024/12/28 19:04:26 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error_msg(char *msg)
{
	if (msg && *msg)
		printf("%s", msg);
	return (1);
}


int	ft_is_int(const char *str)
{
	long	number;
	int		sign;

	number = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (number > 214748364 || (number == 214748364 && ((*str - '0' > 7 && sign == 1) || (*str - '0' > 8 && sign == -1))))
			return (0);
		number = number * 10 + (*str - '0');
		str++;
	}
	return (1);
}
