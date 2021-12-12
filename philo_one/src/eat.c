/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:49:36 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/12 14:50:20 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philosophers.h"

unsigned long	get_stamp(t_phil_state *p_phil)
{
	return (get_time() - p_phil->start_t);
}

static void	rfork(pthread_mutex_t *forks, t_phil_state *p_st, int take)
{
	if (take)
		pthread_mutex_lock(&forks[p_st->pos]);
	else
		pthread_mutex_unlock(&forks[p_st->pos]);
}

static void	lfork(pthread_mutex_t *forks, int pos, t_phil_state *p_st, int take)
{
	if (take)
		pthread_mutex_lock(&forks[(pos + 1) % p_st->phils_total]);
	else
		pthread_mutex_unlock(&forks[(pos + 1) % p_st->phils_total]);
}

static void	take_forks(t_phil_state *p_phil)
{
	if (p_phil->pos == p_phil->phils_total - 1)
	{
		lfork(p_phil->forks, p_phil->pos, p_phil, 1);
		pthread_mutex_lock(p_phil->state_mtx);
		atomic_status_prntr(MESSAGE_TAKE, p_phil, p_phil->pos + 1);
		pthread_mutex_unlock(p_phil->state_mtx);
		rfork(p_phil->forks, p_phil, 1);
		pthread_mutex_lock(p_phil->state_mtx);
		atomic_status_prntr(MESSAGE_TAKE, p_phil, p_phil->pos + 1);
		pthread_mutex_unlock(p_phil->state_mtx);
	}
	else
	{
		rfork(p_phil->forks, p_phil, 1);
		pthread_mutex_lock(p_phil->state_mtx);
		atomic_status_prntr(MESSAGE_TAKE, p_phil, p_phil->pos + 1);
		pthread_mutex_unlock(p_phil->state_mtx);
		lfork(p_phil->forks, p_phil->pos, p_phil, 1);
		pthread_mutex_lock(p_phil->state_mtx);
		atomic_status_prntr(MESSAGE_TAKE, p_phil, p_phil->pos + 1);
		pthread_mutex_unlock(p_phil->state_mtx);
	}
}

static void	put_forks(t_phil_state *p_phil)
{
	if (p_phil->pos == p_phil->phils_total - 1)
	{
		lfork(p_phil->forks, p_phil->pos, p_phil, 0);
		rfork(p_phil->forks, p_phil, 0);
	}
	else
	{
		rfork(p_phil->forks, p_phil, 0);
		lfork(p_phil->forks, p_phil->pos, p_phil, 0);
	}
}

int	eat(t_phil_state *p_phil)
{
	while (p_phil->should_sleep)
		usleep(1000);
	take_forks(p_phil);
	pthread_mutex_lock(p_phil->state_mtx);
	if (p_phil->is_alive)
	{
		p_phil->eat_stamp = get_time();
		atomic_status_prntr(MESSAGE_EAT, p_phil, p_phil->pos + 1);
		p_phil->num_to_eat--;
	}
	pthread_mutex_unlock(p_phil->state_mtx);
	usleep(p_phil->time_to_eat * 1000);
	pthread_mutex_lock(p_phil->state_mtx);
	put_forks(p_phil);
	if ((p_phil->is_alive) && (p_phil->num_to_eat || p_phil->eat_forever))
		atomic_status_prntr(MESSAGE_SLEEP, p_phil, p_phil->pos + 1);
	pthread_mutex_unlock(p_phil->state_mtx);
	usleep(p_phil->time_to_sleep * 1000);
	return (1);
}