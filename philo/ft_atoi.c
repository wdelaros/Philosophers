/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 20:13:06 by wdelaros          #+#    #+#             */
/*   Updated: 2023/06/18 10:21:42 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_min_max(long int num)
{
	if (num > 2147483647 || num < 0)
		return (-42);
	return (num);
}

/// @brief Converts a string to an integer.
/// @param str The string to convert.
/// @return The converted integer value.
int	ft_atoi(const char *str)
{
	long int	num;
	int			i;
	int			neg;

	num = 0;
	i = 0;
	neg = 1;
	if (!str)
		return (0);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 43)
		i++;
	else if (str[i] == 45)
	{
		neg *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		num *= 10;
		num += str[i] - 48;
		i++;
	}
	return (check_min_max(num * neg));
}
