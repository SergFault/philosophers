/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:49:36 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/11 19:04:54 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	phil_sleep(t_phil_state *p_phil)
{
	pthread_mutex_lock(p_phil->state_mtx);
	if ((p_phil->is_alive) && (p_phil->num_to_eat || p_phil->eat_forever)
									&& check_time(p_phil))
		atomic_status_prntr(MESSAGE_SLEEP, p_phil, p_phil->pos + 1);
	pthread_mutex_unlock(p_phil->state_mtx);
	usleep(p_phil->time_to_sleep * 1000);
}

void	think(t_phil_state *p_phil)
{
	pthread_mutex_lock(p_phil->state_mtx);
	if ((p_phil->is_alive) && (p_phil->num_to_eat || p_phil->eat_forever)
		&& check_time(p_phil))
		atomic_status_prntr(MESSAGE_THINK, p_phil, p_phil->pos + 1);
	pthread_mutex_unlock(p_phil->state_mtx);
}
