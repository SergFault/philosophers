/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:49:36 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/13 21:49:29 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	think(t_phil_state *p_phil)
{
	pthread_mutex_lock(p_phil->state_mtx[state_mtx]);
	if ((p_phil->is_alive) && (p_phil->num_to_eat || p_phil->eat_forever)
		&& check_time(p_phil))
		atomic_status_prntr(MESSAGE_THINK, p_phil, p_phil->pos + 1);
	pthread_mutex_unlock(p_phil->state_mtx[state_mtx]);
}

void	*philo_live(void *philo)
{
	t_phil_state	*phil;

	phil = ((t_phil_state *) philo);
	while ((phil->num_to_eat || phil->eat_forever) && phil->is_alive)
	{
		eat(phil);
		think(phil);
	}
	phil->can_b_free = 1;
	return (NULL);
}
