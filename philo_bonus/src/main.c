/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:29:09 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/20 00:19:27 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	wait_processes(t_phil_state **state)
{
	int	c;
	int	n;
	int	status;

	n = state[0]->phils_total;
	c = 0;
	while (c < n)
	{
		waitpid(-1, &status, 0);
		if (status)
		{
			c = 0;
			while (c < n)
				kill(state[c++]->proc_id, 15);
			break ;
		}
		c++;
	}
	return (1);
}

int	launch_processes(t_phil_state **state)
{
	int				i;
	unsigned long	init_stamp;

	i = 0;
	init_stamp = get_time();
	while (i < state[0]->phils_total)
		state[i++]->start_t = init_stamp;
	i = 0;
	while (i < state[0]->phils_total)
	{
		state[i]->proc_id = fork();
		if (state[i]->proc_id == 0)
			philo_live(state[i]);
		i++;
		usleep(100);
	}
	wait_processes(state);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_phil_state	**phils;

	if (init(argc, argv, &phils))
		return (1);
	init_stamps(phils, phils[0]->phils_total);
	launch_processes(phils);
	return (0);
}
