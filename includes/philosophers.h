/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <Degei411233@outlook.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:03:50 by Degef             #+#    #+#             */
/*   Updated: 2023/05/23 16:55:50 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdint.h>
# include <stdint.h>

typedef struct s_philos
{
	int				id;
	int				fork_r;
	int				fork_l;
	long long		last_meal;
	pthread_t		thread;
	struct s_data	*data;
}	t_philos;

typedef struct s_data
{
	int				n_philos;
	long long		t_die;
	long long		t_eat;
	long long		t_sleep;
	long long		start_time;
	int				num_to_eat;
	int				total_no_meals;
	t_philos		*t_philos;
	pthread_mutex_t	num_meals_locker;
	pthread_mutex_t	last_meal_locker;
	pthread_mutex_t	end_g;
	pthread_mutex_t	*fork_locker;
	int				end_game;
	int				*fork;
}	t_data;

// libft
int			ft_atoi(const	char *nptr);
int			ft_isdigit(int c);
void		*ft_calloc(size_t count, size_t size);

// init
int			init_data(int argc, char **argv, t_data *data);
int			init_philos(t_data *data);
void		death_checker(t_philos *philo);
int			int_overflow_check(t_data *data, char **argv);
// utils
int			check_args(char **args);
long long	timestamp(void);
void		destroy_all(t_data *data);
long long	real_time(t_philos *philo);
int			display(t_philos *philo, char *str, long long time, int i);

// philo
void		*philo_life(void *phi);
void		launch_philo(t_data *data);
void		meal_num_checker(t_data *data);

//table manners
void		take_fork(t_philos *philo);
void		eat_philo(t_philos *philo);
void		sleep_philo(t_philos *philo);
void		think_philo(t_philos *philo);
void		ft_usleep(long long t_2_wait, t_philos *philo);

#endif
