/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <Degei411233@outlook.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:59:12 by Degef             #+#    #+#             */
/*   Updated: 2023/05/25 18:53:56 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	init_data(int ac, char **argv, t_data *data)
{
	data->n_philos = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	data->end_game = 0;
	data->start_time = timestamp();
	data->total_no_meals = 0;
	data->num_to_eat = 0;
	if (ac == 6)
		data->num_to_eat = ft_atoi(argv[5]);
	if (data->n_philos <= 0 || data->t_die <= 0
		|| data->t_eat <= 0 || data->t_sleep <= 0 || data->num_to_eat < 0)
	{
		printf("%s\n", "\033[1;31m Invalid Arguments \033[0m");
		free(data);
		return (1);
	}
	data->t_philos = ft_calloc(data->n_philos, sizeof(t_philos));
	pthread_mutex_init(&data->num_meals_locker, NULL);
	pthread_mutex_init(&data->last_meal_locker, NULL);
	pthread_mutex_init(&data->end_g, NULL);
	data->fork = ft_calloc(data->n_philos, sizeof(int));
	data->fork_locker = ft_calloc(data->n_philos, sizeof(pthread_mutex_t));
	init_philos(data);
	return (0);
}

int	init_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philos)
	{
		data->t_philos[i].data = data;
		data->t_philos[i].id = i + 1;
		data->t_philos[i].last_meal = timestamp();
		data->fork[i] = 0;
		pthread_mutex_init(&data->fork_locker[i], NULL);
		data->t_philos[i].fork_r = i;
		if (data->n_philos > 1)
			data->t_philos[i].fork_l = (i + 1) % data->n_philos;
	}
	return (0);
}
