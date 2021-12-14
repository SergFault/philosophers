/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 16:43:02 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/13 16:47:35 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	set_all_dead(t_phil_state **phils)
{
	int	c;

	c = 0;
	while (c < phils[0]->phils_total)
	{
		phils[c++]->is_alive = 0;
	}
}

int	check_time(t_phil_state *phil)
{
	if (get_time() - phil->eat_stamp >= phil->time_to_die)
		return (0);
	return (1);
}

static int	check_dead(t_phil_state **phils, int pos)
{
	if (get_time() - phils[pos]->eat_stamp >= phils[pos]->time_to_die)
	{
		pthread_mutex_lock(phils[pos]->state_mtx[state_mtx]);
		phils[pos]->is_alive = 0;
		set_all_dead(phils);
		atomic_status_prntr(MESSAGE_DIE, phils[pos], phils[pos]->pos + 1);
		pthread_mutex_unlock(phils[pos]->state_mtx[state_mtx]);
		return (1);
	}
	return (0);
}

void	check_philos(t_phil_state **phils, int n)
{
	int	at_least_one;
	int	c;

	at_least_one = 1;
	while (at_least_one)
	{
		c = 0;
		at_least_one = 0;
		while (c < n)
		{
			if (phils[c]->num_to_eat || phils[c]->eat_forever)
			{
				at_least_one = 1;
				if (check_dead(phils, c))
				{
					wait_resources(phils);
					return ;
				}
			}
			c++;
		}
	}
}
