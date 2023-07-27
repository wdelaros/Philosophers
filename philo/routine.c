/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:00:33 by wdelaros          #+#    #+#             */
/*   Updated: 2023/07/27 09:17:07 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	go_eat(t_philo *philo)
{
	usleep(150);
	while (!check_key(philo) || philo->last_eat <= get_time())
	{
		if (philo->last_eat <= get_time())
		{
			is_death(philo);
			return ;
		}
		if (check_status(philo))
			break ;
		usleep(100);
	}
	pthread_mutex_lock(&(philo->l_fork.fork));
	print(philo, FORK);
	pthread_mutex_lock(&philo->r_fork->fork);
	print(philo, FORK);
	print(philo, EAT);
	philo->last_eat = get_time() + philo->data->time_to_die;
	ssleep(philo, philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->r_fork->fork);
	pthread_mutex_unlock(&(philo->l_fork.fork));
	pthread_mutex_lock(&philo->data->mutex_fork);
	philo->r_fork->lock = 0;
	philo->l_fork.lock = 0;
	pthread_mutex_unlock(&philo->data->mutex_fork);
}

int	check_key(t_philo	*philo)
{
	int	res;

	pthread_mutex_lock(&philo->data->mutex_fork);
	if (&philo->l_fork.fork == &philo->r_fork->fork)
		res = 0;
	else if (!philo->r_fork->lock && !philo->l_fork.lock)
	{
		philo->l_fork.lock = 1;
		philo->r_fork->lock = 1;
		res = 1;
	}
	else
		res = 0;
	pthread_mutex_unlock(&philo->data->mutex_fork);
	return (res);
}

int	check_status(t_philo *philo)
{
	int	res;

	pthread_mutex_lock(&philo->data->mutex_death);
	if (philo->data->death)
		res = 1;
	else
		res = 0;
	pthread_mutex_unlock(&philo->data->mutex_death);
	return (res);
}

void	is_death(t_philo	*philo)
{
	pthread_mutex_lock(&philo->data->mutex_death);
	if (!philo->data->death)
	{
		philo->died = 1;
		philo->data->death = 1;
		pthread_mutex_unlock(&philo->data->mutex_death);
		print(philo, DIED);
		return ;
	}
	pthread_mutex_unlock(&philo->data->mutex_death);
}

void	*routine(void *tmp_philo)
{
	t_philo		*philo;

	philo = (t_philo *)tmp_philo;
	if (philo->data->max_eat && !philo->nb_eat)
		return (NULL);
	philo->last_eat = get_time() + philo->data->time_to_die;
	if (philo->id & 1)
		ssleep(philo, philo->data->time_to_eat);
	while (!check_status(philo))
	{
		print(philo, THINK);
		if (!check_status(philo))
			go_eat(philo);
		if (philo->data->max_eat && !--philo->nb_eat)
			return (NULL);
		if (!check_status(philo))
			print(philo, SLEEP);
		ssleep(philo, philo->data->time_to_sleep);
	}
	return (NULL);
}
