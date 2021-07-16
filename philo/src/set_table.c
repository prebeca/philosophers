/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 12:53:58 by user42            #+#    #+#             */
/*   Updated: 2021/06/24 15:38:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	give_fork(t_table *table, int index)
{
	pthread_mutex_t	*fork_mutex;

	fork_mutex = malloc(sizeof(pthread_mutex_t));
	if (fork_mutex == NULL)
		return (1);
	pthread_mutex_init(fork_mutex, NULL);
	table->philosophers[index].right_fork = fork_mutex;
	if (table->rules.number_of_philo > 1)
	{
		if (index + 1 >= table->rules.number_of_philo)
			table->philosophers[0].left_fork = fork_mutex;
		else
			table->philosophers[index + 1].left_fork = fork_mutex;
	}
	return (0);
}

int	set_table(t_table *table)
{
	int	i;

	table->philosophers = malloc(sizeof(t_philo)
			* table->rules.number_of_philo);
	if (table->philosophers == NULL)
		return (1);
	i = -1;
	while (++i < table->rules.number_of_philo)
		table->philosophers[i].left_fork = NULL;
	i = -1;
	pthread_mutex_init(&table->rules.death_mutex, NULL);
	while (++i < table->rules.number_of_philo)
	{
		pthread_mutex_init(&table->philosophers[i].death_eat_mutex, NULL);
		table->philosophers[i].id = i + 1;
		table->philosophers[i].rules = &table->rules;
		table->philosophers[i].time_eat = 0;
		if (give_fork(table, i) != 0)
			return (1);
	}
	return (0);
}
