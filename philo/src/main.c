/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 11:25:32 by user42            #+#    #+#             */
/*   Updated: 2021/06/17 12:22:53 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (check_args(argc, argv))
		return (1);
	if (get_rules(&table.rules, argc, argv))
		return (1);
	if (set_table(&table))
		return (1);
	if (start_life_cycle(&table))
		return (1);
	clean_table(&table);
	return (0);
}
