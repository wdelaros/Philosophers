/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 11:14:40 by wdelaros          #+#    #+#             */
/*   Updated: 2023/07/27 08:19:44 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define FORK "has taken a fork"
# define L_FORK "has taken left fork"
# define R_FORK "has taken right fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIED "died"

typedef struct s_fork
{
	int					lock;
	pthread_mutex_t		fork;
}				t_fork;

typedef struct s_data
{
	long int		start_time;
	int				nb_philo;
	long long int	time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	int				loop_philo;
	int				max_eat;
	int				death;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_fork;
	pthread_mutex_t	mutex_death;
	struct s_philo	*philo;
}				t_data;

typedef struct s_philo
{
	int					id;
	int					died;
	long long int		nb_eat;
	long long int		last_eat;
	pthread_t			thread;
	t_data				*data;
	t_fork				*r_fork;
	t_fork				l_fork;
}				t_philo;

void			*routine(void *tmp_philo);

long long int	get_time(void);
int				check_value(t_data *data, int argc, char *argv[]);
void			is_death(t_philo	*philo);
void			print(t_philo *philo, char	*str);

int				ft_atoi(const char *str);

int				ft_isnumber(char *str);
int				check_status(t_philo *philo);
void			ssleep(t_philo *philo, long long int time);
int				check_key(t_philo	*philo);

#endif