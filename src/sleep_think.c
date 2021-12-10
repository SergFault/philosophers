/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:49:36 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/07 19:08:45 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	phil_sleep(t_phil_state *p_phil)
{
	pthread_mutex_lock(p_phil->state_mtx);
	if (p_phil->is_alive)
		atomic_status_prntr(MESSAGE_SLEEP, get_stamp(p_phil), p_phil->pos + 1);
	pthread_mutex_unlock(p_phil->state_mtx);
	usleep(p_phil->time_to_sleep * 1000);
}

void	think(t_phil_state *p_phil)
{
	pthread_mutex_lock(p_phil->state_mtx);
	if (p_phil->is_alive)
		atomic_status_prntr(MESSAGE_THINK, get_stamp(p_phil), p_phil->pos + 1);
	pthread_mutex_unlock(p_phil->state_mtx);
}
