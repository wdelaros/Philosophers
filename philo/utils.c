/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:02:34 by wdelaros          #+#    #+#             */
/*   Updated: 2023/07/27 09:13:11 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long int	get_time(void)
{
	static struct timeval	start = {-1, -1};
	struct timeval			now;

	if (start.tv_sec == -1 && start.tv_usec == -1)
		gettimeofday(&start, NULL);
	gettimeofday(&now, NULL);
	return (((now.tv_sec * 1000 - start.tv_sec * 1000) + \
	(now.tv_usec / 1000 - start.tv_usec / 1000)));
}

void	ssleep(t_philo *philo, long long int time)
{
	long long int	start;

	start = get_time();
	if (philo->last_eat < time + start && !philo->died && \
	philo->last_eat > start)
	{
		usleep((philo->last_eat - start) * 1000);
		is_death(philo);
	}
	else
	{
		usleep(time * 900);
		while (get_time() < time + start)
			;
	}
}

int	check_value(t_data *data, int argc, char *argv[])
{
	int	i;

	i = 0;
	while (++i < argc)
		if (!ft_isnumber(argv[i]))
			return (0);
	i = 0;
	data->death = 0;
	while (++i < argc)
		if (ft_atoi(argv[i]) == -42)
			return (0);
	data->nb_philo = ft_atoi(argv[1]);
	if (data->nb_philo > 200)
		return (0);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->loop_philo = 0;
	if (argc == 6)
		data->max_eat = 1;
	else
		data->max_eat = 0;
	if (data->max_eat)
		data->loop_philo = ft_atoi(argv[5]);
	return (1);
}

void	print(t_philo *philo, char	*str)
{
	pthread_mutex_lock(&(philo->data->mutex_print));
	if (!check_status(philo) || (check_status(philo) && philo->died))
		printf("%lld %d %s\n", get_time(), philo->id, str);
	pthread_mutex_unlock(&(philo->data->mutex_print));
}
