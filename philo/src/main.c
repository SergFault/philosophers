/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:29:09 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/20 19:08:02 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	create_philo_threads(t_phil_state	**phils)
{
	int	i;

	i = 0;
	while (i < (*phils)[0].phils_total)
	{
		if (pthread_create(&phils[i]->t, NULL, philo_live, phils[i])
			|| pthread_detach(phils[i]->t))
		{
			free_resources(phils, phils[0]->phils_total);
			return (process_fail(ERR_THREAD, 1));
		}
		i++;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_phil_state	**phils;

	if (init(argc, argv, &phils))
		return (1);
	init_stamps(phils, phils[0]->phils_total);
	if (create_philo_threads(phils))
		return (1);
	check_philos(phils, (*phils)[0].phils_total);
	usleep(1000);
	free_resources(phils, phils[0]->phils_total);
	return (0);
}
