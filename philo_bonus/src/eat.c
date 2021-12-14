/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:49:36 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/13 22:08:32 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philosophers.h"

static void	take_forks(t_phil_state *p_phil)
{
	pthread_mutex_lock(p_phil->state_mtx[lock_mtx]);
	sem_wait(p_phil->forks);
	pthread_mutex_lock(p_phil->state_mtx[state_mtx]);
	atomic_status_prntr(MESSAGE_TAKE, p_phil, p_phil->pos + 1);
	pthread_mutex_unlock(p_phil->state_mtx[state_mtx]);
	sem_wait(p_phil->forks);
	pthread_mutex_lock(p_phil->state_mtx[state_mtx]);
	atomic_status_prntr(MESSAGE_TAKE, p_phil, p_phil->pos + 1);
	pthread_mutex_unlock(p_phil->state_mtx[state_mtx]);
	pthread_mutex_unlock(p_phil->state_mtx[lock_mtx]);
}

static void	put_forks(t_phil_state *p_phil)
{
	sem_post(p_phil->forks);
	sem_post(p_phil->forks);
}

int	eat(t_phil_state *p_phil)
{
	while (p_phil->should_sleep && p_phil->is_alive)
		usleep(1000);
	take_forks(p_phil);
	pthread_mutex_lock(p_phil->state_mtx[state_mtx]);
	if (p_phil->is_alive)
	{
		p_phil->eat_stamp = get_time();
		atomic_status_prntr(MESSAGE_EAT, p_phil, p_phil->pos + 1);
		p_phil->num_to_eat--;
	}
	pthread_mutex_unlock(p_phil->state_mtx[state_mtx]);
	usleep(p_phil->time_to_eat * 1000);
	pthread_mutex_lock(p_phil->state_mtx[state_mtx]);
	put_forks(p_phil);
	if ((p_phil->is_alive) && (p_phil->num_to_eat || p_phil->eat_forever))
		atomic_status_prntr(MESSAGE_SLEEP, p_phil, p_phil->pos + 1);
	pthread_mutex_unlock(p_phil->state_mtx[state_mtx]);
	usleep(p_phil->time_to_sleep * 1000);
	return (1);
}
