/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:49:36 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/20 23:24:04 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	think_sleep(t_phil_state *p_phil)
{
	atomic_status_prntr(MESSAGE_SLEEP, p_phil, p_phil->pos + 1);
	precise_sleep(p_phil->time_to_sleep * 1000);
	atomic_status_prntr(MESSAGE_THINK, p_phil, p_phil->pos + 1);
	pthread_mutex_lock(p_phil->line1);
	pthread_mutex_lock(p_phil->line2);
	pthread_mutex_unlock(p_phil->line1);
	pthread_mutex_lock(p_phil->line3);
	pthread_mutex_unlock(p_phil->line2);
	precise_sleep(1000);
	pthread_mutex_unlock(p_phil->line3);
	return (1);
}

static int	is_enough(t_phil_state *p_phil)
{
	if (p_phil->num_to_eat <= 0 && p_phil->eat_forever == 0)
	{
		pthread_mutex_unlock(p_phil->state_mtx);
		pthread_mutex_unlock(p_phil->l_fork);
		pthread_mutex_unlock(p_phil->r_fork);
		return (1);
	}
	return (0);
}

int	eat(t_phil_state *p_phil)
{
	pthread_mutex_lock(p_phil->l_fork);
	atomic_status_prntr(MESSAGE_TAKE, p_phil, p_phil->pos + 1);
	if (p_phil->phils_total == 1)
	{
		while (p_phil[0].is_alive)
			usleep(1000);
		return (0);
	}
	pthread_mutex_lock(p_phil->r_fork);
	atomic_status_prntr(MESSAGE_TAKE, p_phil, p_phil->pos + 1);
	pthread_mutex_lock(p_phil->state_mtx);
	if (p_phil->is_alive)
	{
		p_phil->eat_stamp = get_time();
		atomic_status_prntr(MESSAGE_EAT, p_phil, p_phil->pos + 1);
		p_phil->num_to_eat--;
		if (is_enough(p_phil))
			return (0);
	}
	pthread_mutex_unlock(p_phil->state_mtx);
	precise_sleep(p_phil->time_to_eat * 1000);
	pthread_mutex_unlock(p_phil->l_fork);
	pthread_mutex_unlock(p_phil->r_fork);
	return (think_sleep(p_phil));
}
