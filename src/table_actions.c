/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <Degei411233@outlook.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:09:00 by Degef             #+#    #+#             */
/*   Updated: 2023/05/25 18:54:08 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	take_fork_even(t_philos *philo)
{
	pthread_mutex_lock(&philo->data->fork_locker[philo->fork_r]);
	pthread_mutex_lock(&philo->data->fork_locker[philo->fork_l]);
	while (philo->data->fork[philo->fork_l] || philo->data->fork[philo->fork_r])
	{
		pthread_mutex_unlock(&philo->data->fork_locker[philo->fork_r]);
		pthread_mutex_unlock(&philo->data->fork_locker[philo->fork_l]);
		usleep(100);
		pthread_mutex_lock(&philo->data->fork_locker[philo->fork_r]);
		pthread_mutex_lock(&philo->data->fork_locker[philo->fork_l]);
	}
	philo->data->fork[philo->fork_l] = 1;
	philo->data->fork[philo->fork_r] = 1;
	pthread_mutex_unlock(&philo->data->fork_locker[philo->fork_r]);
	pthread_mutex_unlock(&philo->data->fork_locker[philo->fork_l]);
	display(philo, " \e[0;32m🥄 has taken  fork \033[0m", real_time(philo), 0);
	display(philo, " \e[0;32m🥄 has taken  fork \033[0m", real_time(philo), 0);
}

void	take_fork(t_philos *philo)
{
	if (philo->id % 2 != 0)
	{
		usleep(1500);
		pthread_mutex_lock(&philo->data->fork_locker[philo->fork_l]);
		pthread_mutex_lock(&philo->data->fork_locker[philo->fork_r]);
		while (philo->data->fork[philo->fork_l]
			|| philo->data->fork[philo->fork_r])
		{
			pthread_mutex_unlock(&philo->data->fork_locker[philo->fork_l]);
			pthread_mutex_unlock(&philo->data->fork_locker[philo->fork_r]);
			usleep(100);
			pthread_mutex_lock(&philo->data->fork_locker[philo->fork_l]);
			pthread_mutex_lock(&philo->data->fork_locker[philo->fork_r]);
		}
		philo->data->fork[philo->fork_l] = 1;
		philo->data->fork[philo->fork_r] = 1;
		pthread_mutex_unlock(&philo->data->fork_locker[philo->fork_l]);
		pthread_mutex_unlock(&philo->data->fork_locker[philo->fork_r]);
		display(philo, " \e[0;32m🥄 has taken  fork \033[0m", real_time(philo), 0);
		display(philo, " \e[0;32m🥄 has taken  fork \033[0m", real_time(philo), 0);
	}
	else
		take_fork_even(philo);
}

void	eat_philo(t_philos *philo)
{
	pthread_mutex_lock(&philo->data->end_g);
	if (philo->data->end_game == 0)
	{
		pthread_mutex_unlock(&philo->data->end_g);
		take_fork(philo);
		display(philo, "\e[0;33m 🍽  is eating \033[0m", real_time(philo), 0);
		pthread_mutex_lock(&philo->data->last_meal_locker);
		philo->last_meal = timestamp();
		pthread_mutex_unlock(&philo->data->last_meal_locker);
		pthread_mutex_lock(&philo->data->num_meals_locker);
		philo->data->total_no_meals++;
		pthread_mutex_unlock(&philo->data->num_meals_locker);
		ft_usleep(philo->data->t_eat, philo);
		pthread_mutex_lock(&philo->data->fork_locker[philo->fork_l]);
		philo->data->fork[philo->fork_l] = 0;
		pthread_mutex_unlock(&philo->data->fork_locker[philo->fork_l]);
		pthread_mutex_lock(&philo->data->fork_locker[philo->fork_r]);
		philo->data->fork[philo->fork_r] = 0;
		pthread_mutex_unlock(&philo->data->fork_locker[philo->fork_r]);
		return ;
	}
	pthread_mutex_unlock(&philo->data->end_g);
}

void	ft_usleep(long long t_2wait, t_philos *philo)
{
	long long	current_time;

	current_time = timestamp();
	pthread_mutex_lock(&philo->data->end_g);
	if (philo->data->end_game != 0)
	{
		pthread_mutex_unlock(&philo->data->end_g);
		return ;
	}
	pthread_mutex_unlock(&philo->data->end_g);
	while (timestamp() - current_time < t_2wait)
		usleep(100);
}
