/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 11:27:22 by user42            #+#    #+#             */
/*   Updated: 2021/07/12 14:29:15 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_rules
{
	int				number_of_philo;
	int				max_time_eat;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				death_flag;
	pthread_mutex_t	death_mutex;
	int				number_finished_eat;
	struct timeval	time_ref;
	pthread_mutex_t	stdout_mutex;
	pthread_mutex_t	finished_eat_mutex;
}				t_rules;

typedef struct s_philo
{
	int				id;
	int				time_eat;
	struct timeval	last_time_eat;
	t_rules			*rules;
	pthread_t		thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	death_eat_mutex;
}				t_philo;

typedef struct s_table
{
	t_philo	*philosophers;
	t_rules	rules;
}				t_table;

int				check_args(int argc, char **argv);
int				get_rules(t_rules *rules, int argc, char **argv);
int				set_table(t_table *table);
int				start_life_cycle(t_table *table);
void			clean_table(t_table *table);

/*
** Utils
*/
int				get_time_elapsed(struct timeval ref_time);
void			mutexed_printf(t_philo *philo, char *state);
void			check_finished_eat(t_philo *philo);
int				is_someone_dead(t_rules	*rules);

#endif
