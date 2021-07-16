/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 14:04:23 by user42            #+#    #+#             */
/*   Updated: 2021/07/12 14:29:53 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	get_time_elapsed(struct timeval ref_time)
{
	int				time_ms;
	int				ref_time_ms;
	struct timeval	time;

	gettimeofday(&time, NULL);
	time_ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	ref_time_ms = ref_time.tv_sec * 1000 + ref_time.tv_usec / 1000;
	return (time_ms - ref_time_ms);
}

void	clean_table(t_table *table)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&table->rules.death_mutex);
	while (++i < table->rules.number_of_philo)
	{
		pthread_mutex_destroy(table->philosophers[i].right_fork);
		free(table->philosophers[i].right_fork);
	}
	free(table->philosophers);
}

void	mutexed_printf(t_philo *philo, char *state)
{
	pthread_mutex_lock(&philo->rules->stdout_mutex);
	if (!is_someone_dead(philo->rules))
		printf("%8dms|%3d %s\n", get_time_elapsed(philo->rules->time_ref),
			philo->id, state);
	pthread_mutex_unlock(&philo->rules->stdout_mutex);
}

void	check_finished_eat(t_philo *philo)
{
	if (philo->rules->max_time_eat != -1
		&& philo->time_eat >= philo->rules->max_time_eat)
	{
		pthread_mutex_lock(&philo->rules->finished_eat_mutex);
		philo->rules->number_finished_eat++;
		if (philo->rules->number_finished_eat
			== philo->rules->number_of_philo)
		{
			pthread_mutex_lock(&philo->rules->death_mutex);
			philo->rules->death_flag = 1;
			pthread_mutex_unlock(&philo->rules->death_mutex);
		}
		pthread_mutex_unlock(&philo->rules->finished_eat_mutex);
	}
}

int	is_someone_dead(t_rules	*rules)
{
	int	ret;

	pthread_mutex_lock(&rules->death_mutex);
	ret = rules->death_flag;
	pthread_mutex_unlock(&rules->death_mutex);
	return (ret);
}
