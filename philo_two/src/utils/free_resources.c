/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 18:21:12 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/13 21:20:59 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	free_resources(t_phil_state **phils, int n)
{
	int	c;

	c = 0;
	if (phils)
	{
		if (*phils && phils[0]->state_mtx[state_mtx])
		{
			pthread_mutex_destroy(phils[0]->state_mtx[state_mtx]);
			free(phils[0]->state_mtx[state_mtx]);
		}
		if (*phils && phils[0]->state_mtx[lock_mtx])
		{
			pthread_mutex_destroy(phils[0]->state_mtx[lock_mtx]);
			free(phils[0]->state_mtx[lock_mtx]);
		}
		sem_close(phils[0]->forks);
		c = 0;
		while (c < n)
			free(phils[c++]);
		free(phils);
	}
}

void	wait_resources(t_phil_state **phils)
{
	int	c;
	int	should_wait;

	c = 0;
	should_wait = 1;
	while (should_wait)
	{
		should_wait = 0;
		c = 0;
		while (c < phils[0]->phils_total)
		{
			if (phils[c]->can_b_free == 0)
				should_wait = 1;
			c++;
		}
		if (should_wait == 0)
			return ;
		usleep(1000);
	}
}
