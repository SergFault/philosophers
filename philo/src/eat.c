/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:49:36 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/20 18:23:49 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philosophers.h"

int	eat(t_phil_state *p_phil)
{
	pthread_mutex_lock(p_phil->line1);
	pthread_mutex_lock(p_phil->line2);
	pthread_mutex_unlock(p_phil->line1);
	pthread_mutex_lock(p_phil->line3);
	pthread_mutex_unlock(p_phil->line2);
	pthread_mutex_unlock(p_phil->line3);
	pthread_mutex_lock(p_phil->l_fork);
	atomic_status_prntr(MESSAGE_TAKE, p_phil, p_phil->pos + 1);
	pthread_mutex_lock(p_phil->r_fork);
	atomic_status_prntr(MESSAGE_TAKE, p_phil, p_phil->pos + 1);
	pthread_mutex_lock(p_phil->state_mtx);
	if (p_phil->is_alive)
	{
		p_phil->eat_stamp = get_time();
		atomic_status_prntr(MESSAGE_EAT, p_phil, p_phil->pos + 1);
		p_phil->num_to_eat--;
	}
	pthread_mutex_unlock(p_phil->state_mtx);
	precise_sleep(p_phil->time_to_eat * 1000);
	pthread_mutex_lock(p_phil->state_mtx);
	pthread_mutex_unlock(p_phil->l_fork);
	pthread_mutex_unlock(p_phil->r_fork);
	if ((p_phil->is_alive) && (p_phil->num_to_eat || p_phil->eat_forever))
		atomic_status_prntr(MESSAGE_SLEEP, p_phil, p_phil->pos + 1);
	pthread_mutex_unlock(p_phil->state_mtx);
	precise_sleep(p_phil->time_to_sleep * 1000);
	return (1);
}
