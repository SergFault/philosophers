/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:31:47 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/14 14:15:16 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	validate_args(int argc, char *argv[])
{
	int	c;

	if (argc < 5 || argc > 6)
		return (process_fail(ERR_ARGS, 1));
	c = 1;
	while (c < argc)
	{
		if (!contains_only_nums(argv[c++]))
		{
			return (process_fail(ERR_ARGINT, 1));
		}
	}
	return (0);
}

static int	get_params(int argc, char *argv[], int params[])
{
	int	status;

	status = 0;
	params[num_to_eat] = 0;
	params[num_philo] = ft_atoi_err(argv[1], &status);
	params[time_to_die] = ft_atoi_err(argv[2], &status);
	params[time_to_eat] = ft_atoi_err(argv[3], &status);
	params[time_to_sleep] = ft_atoi_err(argv[4], &status);
	if (argc == 6)
		params[num_to_eat] = ft_atoi_err(argv[5], &status);
	if (status || params[num_philo] > 250 || params[num_philo] < 1)
		return (process_fail(ERR_ARGINT, 1));
	return (0);
}

int	init(int argc, char *argv[], t_phil_state **phil_st[])
{
	int	params[NUM_PARAM];

	if (validate_args(argc, argv))
		return (1);
	if (get_params(argc, argv, params))
		return (1);
	if (init_philos(phil_st, params))
		return (1);
	return (0);
}
