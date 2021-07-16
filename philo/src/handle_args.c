/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 11:42:30 by user42            #+#    #+#             */
/*   Updated: 2021/06/24 15:38:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isalldigit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}

int	ft_atoi(const char *str)
{
	unsigned int	nbr;
	int				i;
	int				neg;

	nbr = 0;
	i = 0;
	while (str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f'
		|| str[i] == '\r' || str[i] == ' ')
		i++;
	neg = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	return ((int)nbr * neg);
}

int	check_args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		printf("philosophers: wrong number of arguments\n");
		return (1);
	}
	i = 0;
	while (++i < argc)
	{
		if (!ft_isalldigit(argv[i]))
		{
			printf("philosophers: invalid arguments\n");
			return (1);
		}
	}
	return (0);
}

int	get_rules(t_rules *rules, int argc, char **argv)
{
	rules->number_of_philo = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	rules->death_flag = 0;
	rules->number_finished_eat = 0;
	if (pthread_mutex_init(&rules->stdout_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&rules->finished_eat_mutex, NULL))
		return (1);
	if (argc > 5)
		rules->max_time_eat = ft_atoi(argv[5]);
	else
		rules->max_time_eat = -1;
	return (0);
}
