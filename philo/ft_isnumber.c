/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 22:06:33 by wdelaros          #+#    #+#             */
/*   Updated: 2023/06/18 10:25:25 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == 43 || str[i] == 45)
		{
			i++;
			if (str[i] < 48 || str[i] > 57)
				return (0);
		}
		else if (str[i] < 48 || str[i] > 57)
			return (0);
		i++;
	}
	return (1);
}
