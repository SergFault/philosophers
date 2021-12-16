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

static void	take_forks(t_phil_state *p_phil)
{
	int	first_f;
	int	second_f;

	calculate_fork(p_phil, &first_f, &second_f);
	take_fork(p_phil->forks, first_f, 1);
	pthread_mutex_lock(p_phil->state_mtx);
	atomic_status_prntr(MESSAGE_TAKE, p_phil, p_phil->pos + 1);
	pthread_mutex_unlock(p_phil->state_mtx);
	if (p_phil->phils_total == 1)
	{
		while (p_phil->is_alive)
			precise_sleep(p_phil->time_to_eat);
		return ;
	}
	take_fork(p_phil->forks, second_f, 1);
	pthread_mutex_lock(p_phil->state_mtx);
	atomic_status_prntr(MESSAGE_TAKE, p_phil, p_phil->pos + 1);
	pthread_mutex_unlock(p_phil->state_mtx);
}

int	eat(t_phil_state *p_phil)
{
	while (p_phil->should_sleep && p_phil->is_alive)
		precise_sleep(1000);
	take_forks(p_phil);
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
	put_forks(p_phil);
	if ((p_phil->is_alive) && (p_phil->num_to_eat || p_phil->eat_forever))
		atomic_status_prntr(MESSAGE_SLEEP, p_phil, p_phil->pos + 1);
	pthread_mutex_unlock(p_phil->state_mtx);
	precise_sleep(p_phil->time_to_sleep * 1000);
	return (1);
}
