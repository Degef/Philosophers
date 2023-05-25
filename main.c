/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <Degei411233@outlook.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:21:58 by Degef             #+#    #+#             */
/*   Updated: 2023/05/23 16:14:54 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	launch_philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philos)
	{
		if (pthread_create(&data->t_philos[i].thread, NULL,
				&philo_life, &(data->t_philos[i])) != 0)
			return ;
	}
	i = -1;
	while (data->end_game == 0)
	{
		death_checker(&data->t_philos[++i % data->n_philos]);
		if (data->num_to_eat > 0)
			meal_num_checker(data);
		usleep(500);
	}
}

void	meal_num_checker(t_data *data)
{
	pthread_mutex_lock(&data->num_meals_locker);
	if (data->total_no_meals >= data->n_philos * data->num_to_eat)
	{
		pthread_mutex_unlock(&data->num_meals_locker);
		pthread_mutex_lock(&data->end_g);
		data->end_game = 1;
		pthread_mutex_unlock(&data->end_g);
		return ;
	}
	pthread_mutex_unlock(&data->num_meals_locker);
}

void	death_checker(t_philos *philo)
{
	int	lock;

	lock = 1;
	pthread_mutex_lock(&philo->data->last_meal_locker);
	if (timestamp() - philo->last_meal >= philo->data->t_die)
	{
		pthread_mutex_unlock(&philo->data->last_meal_locker);
		lock = 0;
		pthread_mutex_lock(&philo->data->end_g);
		philo->data->end_game = 1;
		pthread_mutex_unlock(&philo->data->end_g);
		if (philo->data->n_philos != 1)
			display(philo, "😵\033[1;31m died \033[0m", real_time(philo), 1);
	}
	if (lock)
		pthread_mutex_unlock(&philo->data->last_meal_locker);
}

int	main(int ac, char **argv)
{
	t_data	*data;

	if (ac != 5 && ac != 6)
	{
		printf("%s\n", "\033[1;31m Please enter the right arguments: \033[0m");
		printf("%s\n", "Ex: ./philo [num of philo] [time 2 die] [time 2 eat]");
		return (0);
	}
	if (!check_args(argv))
	{
		printf("%s\n", "\033[1;31m Invalid Arguments \033[0m");
		return (0);
	}
	if (ft_atoi(argv[1]) == 0)
	{
		printf("\n%s\n\n", "\033[1;33m Number of philosophers cannot be 0 \033[0m");
		return (0);
	}
	data = ft_calloc(1, sizeof(t_data));
	if (init_data(ac, argv, data))
		return (0);
	launch_philo(data);
	destroy_all(data);
	return (0);
}
