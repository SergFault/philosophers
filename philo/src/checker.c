/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 16:43:02 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/20 23:36:58 by Sergey           ###   ########.fr       */
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

static int	check_dead(t_phil_state **phils, int pos)
{
	pthread_mutex_lock(phils[0]->state_mtx);
	if (get_time() - phils[pos]->eat_stamp >= phils[pos]->time_to_die)
	{
		atomic_status_prntr_dead(phils[pos], phils[pos]->pos + 1);
		set_all_dead(phils);
		pthread_mutex_unlock(phils[pos]->write);
		pthread_mutex_unlock(phils[pos]->state_mtx);
		return (1);
	}
	pthread_mutex_unlock(phils[0]->state_mtx);
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
		usleep(1000);
	}
}
