/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:29:09 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/20 16:13:33 by Sergey           ###   ########.fr       */
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

static int	ft_kill(int n, t_phil_state **phils)
{
	while (--n >= 0)
		kill(phils[n]->proc_id, 15);
	return (process_fail(ERR_PROC, 1));
}

int	launch_processes(t_phil_state **state)
{
	int				i;
	unsigned long	init_stamp;

	i = 0;
	init_stamp = get_time();
	while (i < state[0]->phils_total)
	{
		state[i]->start_t = init_stamp;
		state[i++]->eat_stamp = init_stamp;
	}
	i = 0;
	while (i < state[0]->phils_total)
	{
		state[i]->proc_id = fork();
		if (state[i]->proc_id == -1)
			return (ft_kill(i, state));
		if (state[i]->proc_id == 0)
			philo_start(i, state);
		i++;
		usleep(200);
	}
	wait_processes(state);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_phil_state	**phils;

	if (init(argc, argv, &phils))
		return (1);
	if (launch_processes(phils))
	{
		free_resources(phils);
		return (1);
	}
	free_resources(phils);
	return (0);
}
