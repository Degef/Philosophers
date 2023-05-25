/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <Degei411233@outlook.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:21:54 by Degef             #+#    #+#             */
/*   Updated: 2023/05/23 16:58:14 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	one_philo(t_philos *philo)
{
	pthread_mutex_lock(&philo->data->fork_locker[philo->fork_l]);
	display(philo, " \e[0;32m🥄 has taken  fork \033[0m", real_time(philo), 0);
	ft_usleep(philo->data->t_die, philo);
	display(philo, "😵\033[1;31m died \033[0m", real_time(philo), 1);
	pthread_mutex_lock(&philo->data->end_g);
	philo->data->end_game = 1;
	pthread_mutex_unlock(&philo->data->end_g);
	pthread_mutex_unlock(&philo->data->fork_locker[philo->fork_l]);
}

void	*philo_life(void *phi)
{
	t_philos	*philo;

	philo = (t_philos *)phi;
	if (philo->data->n_philos == 1)
		one_philo(philo);
	pthread_mutex_lock(&philo->data->end_g);
	while (philo->data->end_game == 0)
	{
		pthread_mutex_unlock(&philo->data->end_g);
		eat_philo(philo);
		sleep_philo(philo);
		think_philo(philo);
		pthread_mutex_lock(&philo->data->end_g);
	}
	pthread_mutex_unlock(&philo->data->end_g);
	return (NULL);
}

void	think_philo(t_philos *philo)
{
	pthread_mutex_lock(&philo->data->end_g);
	if (philo->data->end_game == 0)
	{
		pthread_mutex_unlock(&philo->data->end_g);
		display(philo, " \e[0;35m🤔 is thinking \033[0m", real_time(philo), 0);
		return ;
	}
	pthread_mutex_unlock(&philo->data->end_g);
}

void	sleep_philo(t_philos *philo)
{
	pthread_mutex_lock(&philo->data->end_g);
	if (philo->data->end_game == 0)
	{
		pthread_mutex_unlock(&philo->data->end_g);
		display(philo, "\e[0;36m 😴 is sleeping \033[0m", real_time(philo), 0);
		ft_usleep(philo->data->t_sleep, philo);
		return ;
	}
	pthread_mutex_unlock(&philo->data->end_g);
}
