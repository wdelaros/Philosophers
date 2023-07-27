/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:03:37 by wdelaros          #+#    #+#             */
/*   Updated: 2023/07/27 08:57:31 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init(t_data *data)
{
	pthread_mutex_init(&data->mutex_print, NULL);
	pthread_mutex_init(&data->mutex_fork, NULL);
	pthread_mutex_init(&data->mutex_death, NULL);
	data->philo = malloc(data->nb_philo * sizeof(t_philo));
	if (!data->philo)
		return (-1);
	return (0);
}

static void	init_philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].r_fork = NULL;
		data->philo[i].l_fork.lock = 0;
		data->philo[i].data = data;
		data->philo[i].nb_eat = data->loop_philo;
		pthread_mutex_init(&data->philo[i].l_fork.fork, NULL);
		if (i == data->nb_philo - 1)
			data->philo[i].r_fork = &data->philo[0].l_fork;
		else
			data->philo[i].r_fork = &data->philo[i + 1].l_fork;
	}
	i = -1;
	while (++i < data->nb_philo)
		if (pthread_create(&data->philo[i].thread, NULL, &routine, \
		&(data->philo[i])) != 0)
			return ;
	return ;
}

static void	ft_purge(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
		pthread_mutex_destroy(&data->philo[i].l_fork.fork);
	free(data->philo);
	pthread_mutex_destroy(&data->mutex_print);
	pthread_mutex_destroy(&data->mutex_fork);
	pthread_mutex_destroy(&data->mutex_death);
}

static void	ft_error(int i)
{
	if (i == 0)
	{
		printf("Error\nWrong input: %s %s %s %s %s\n",
			"./philo number_of_philosophers", "time_to_die", "time_to_eat",
			"time_to_sleep", "[number_of_times_each_philosopher_must_eat]");
	}
	else
	{
		printf("Error\n");
		printf("Numbers must be positive or a int or less than 200 philo\n");
	}
}

int	main(int argc, char *argv[])
{
	t_data	data;
	int		i;

	if (argc != 6 && argc != 5)
	{
		ft_error(0);
		return (1);
	}
	if (!check_value(&data, argc, argv))
	{
		ft_error(1);
		return (1);
	}
	if (init(&data) == -1)
	{
		ft_purge(&data);
		return (1);
	}
	init_philo(&data);
	i = -1;
	while (++i < data.nb_philo)
		if (pthread_join(data.philo[i].thread, NULL) != 0)
			break ;
	ft_purge(&data);
	return (0);
}
