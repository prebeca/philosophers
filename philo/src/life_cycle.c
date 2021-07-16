/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 13:24:30 by user42            #+#    #+#             */
/*   Updated: 2021/07/06 13:54:01 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*death_loop(void *void_philo)
{
	t_philo	*philo;

	philo = void_philo;
	while (!is_someone_dead(philo->rules))
	{
		pthread_mutex_lock(&philo->death_eat_mutex);
		if (get_time_elapsed(philo->last_time_eat) > philo->rules->time_to_die)
		{
			pthread_mutex_lock(&philo->rules->stdout_mutex);
			pthread_mutex_lock(&philo->rules->death_mutex);
			if (!philo->rules->death_flag)
			{
				philo->rules->death_flag = 1;
				printf("%8dms|%3d %s\n", get_time_elapsed(
						philo->rules->time_ref), philo->id, "died");
			}
			pthread_mutex_unlock(&philo->rules->death_mutex);
			pthread_mutex_unlock(&philo->rules->stdout_mutex);
		}
		pthread_mutex_unlock(&philo->death_eat_mutex);
		usleep(1);
	}
	return (philo);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	mutexed_printf(philo, "has taken a fork");
	while (!philo->left_fork)
	{
		if (is_someone_dead(philo->rules))
		{
			pthread_mutex_unlock(philo->right_fork);
			return ;
		}
	}
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->death_eat_mutex);
	mutexed_printf(philo, "has taken a fork");
	mutexed_printf(philo, "is eating");
	gettimeofday(&philo->last_time_eat, NULL);
	pthread_mutex_unlock(&philo->death_eat_mutex);
	while (!is_someone_dead(philo->rules)
		&& get_time_elapsed(philo->last_time_eat) < philo->rules->time_to_eat)
		usleep(1);
	philo->time_eat++;
	check_finished_eat(philo);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	philo_sleep(t_philo *philo)
{
	struct timeval	start_sleep;

	mutexed_printf(philo, "is sleeping");
	gettimeofday(&start_sleep, NULL);
	while (!is_someone_dead(philo->rules) && get_time_elapsed(start_sleep)
		< philo->rules->time_to_sleep)
		usleep(1);
}

void	*life_cycle(void *void_philo)
{
	t_philo		*philo;
	pthread_t	death_thread;

	philo = void_philo;
	philo->last_time_eat = philo->rules->time_ref;
	pthread_create(&death_thread, NULL, &death_loop, philo);
	check_finished_eat(philo);
	if (!(philo->id % 2))
		usleep(15000);
	while (!is_someone_dead(philo->rules))
	{
		mutexed_printf(philo, "is thinking");
		philo_eat(philo);
		philo_sleep(philo);
	}
	pthread_join(death_thread, NULL);
	return (philo);
}

int	start_life_cycle(t_table *table)
{
	int		i;

	i = -1;
	gettimeofday(&table->rules.time_ref, NULL);
	while (++i < table->rules.number_of_philo)
		pthread_create(&table->philosophers[i].thread, NULL,
			&life_cycle, &table->philosophers[i]);
	i = -1;
	while (++i < table->rules.number_of_philo)
		pthread_join(table->philosophers[i].thread, NULL);
	return (0);
}
