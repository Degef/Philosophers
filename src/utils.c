/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <Degei411233@outlook.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:27:50 by Degef             #+#    #+#             */
/*   Updated: 2023/05/25 18:54:11 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long long	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long long	real_time(t_philos *philo)
{
	return (timestamp() - philo->data->start_time);
}

int	display(t_philos *philo, char *str, long long time, int i)
{
	pthread_mutex_lock(&philo->data->end_g);
	if (philo->data->end_game == 0)
		printf("%s %lld ms  %d %s\n", "⏰", time, philo->id, str);
	else if (i)
		printf("%s %lld ms  %d %s\n", "⏰", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->end_g);
	return (1);
}

void	destroy_all(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philos)
		if (pthread_join(data->t_philos[i].thread, NULL) != 0)
			return ;
	i = -1;
	while (++i < data->n_philos)
		pthread_mutex_destroy(&data->fork_locker[i]);
	pthread_mutex_destroy(&data->num_meals_locker);
	pthread_mutex_destroy(&data->last_meal_locker);
	pthread_mutex_destroy(&data->end_g);
	free (data->t_philos);
	free(data->fork);
	free(data->fork_locker);
	free(data);
}

int	check_args(char **args)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (ft_isdigit(args[i][j]))
				j++;
			else
				return (0);
		}
		i++;
	}
	return (1);
}
