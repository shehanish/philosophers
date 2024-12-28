/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:51:47 by shkaruna          #+#    #+#             */
/*   Updated: 2024/12/28 19:10:24 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

static int	ft_num_len(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	ft_rev_str(char *str)
{
    int		start;
    int		finish;
    char	swap;

    start = 0;
    finish = ft_strlen(str) - 1;
    while (start < finish)
    {
        swap = str[start];
        str[start] = str[finish];
        str[finish] = swap;
        start++;
        finish--;
    }
}

char	*ft_itoa(int num)
{
    char			*str;
    int				len;
    unsigned int	tmp_num;

    len = 0;
    str = malloc(sizeof(*str) * (ft_num_len(num) + 1));
    if (!str)
        return (NULL);
    if (num < 0)
        tmp_num = -1 * num;
    else
        tmp_num = num;
    while (tmp_num != 0)
    {
        str[len++] = (tmp_num % 10) + '0';
        tmp_num /= 10;
    }
    if (num == 0)
        str[len++] = '0';
    if (num < 0)
        str[len++] = '-';
    str[len] = '\0';
    ft_rev_str(str);
    return (str);
}

static int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}
int	ft_atoi(const char *str)
{
    int		index;
    int		sign;
    long	result;

    index = 0;
    result = 0;
    sign = 1;
    while ((str[index] == ' ' || (str[index] >= 9 && str[index] <= 13)))
        index++;
    if (str[index] == '-')
        sign = -1;
    if (str[index] == '-' || str[index] == '+')
        index++;
    while (str[index] != '\0' && ft_isdigit(str[index]))
    {
        if (result > 922337203685477580 || (result == 922337203685477580
                && ((!sign && str[index] - '0' > 7) || (sign && str[index] - '0' > 8))))
            return (-1 * (sign == 1));
        else
            result = (result * 10) + str[index++] - '0';
    }
    return (result * sign);
}
