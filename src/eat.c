/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:49:36 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/07 18:13:32 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philosophers.h"

int	get_stamp(t_phil_state *p_phil)
{
	return (get_time() - p_phil->start_t);
}

static void	rfork(pthread_mutex_t *forks, int pos, int take)
{
	if (take)
		pthread_mutex_lock(&forks[pos]);
	else
		pthread_mutex_unlock(&forks[pos]);
}

static void	lfork(pthread_mutex_t *forks, int pos, int tot_phil, int take)
{
//	printf("fork %d\n", (pos + 2) % tot_phil);
	if (take)
		pthread_mutex_lock(&forks[(pos + 1) % tot_phil]);
	else
		pthread_mutex_unlock(&forks[(pos + 1) % tot_phil]);
}

int	eat(t_phil_state *p_phil)
{
	if (p_phil->pos == p_phil->phils_total - 1)
	{
		lfork(p_phil->forks, p_phil->pos, p_phil->phils_total, 1);
		rfork(p_phil->forks, p_phil->pos, 1);
		p_phil->eat_stamp = get_time();
		atomic_status_prntr(MESSAGE_EAT, get_stamp(p_phil), p_phil->pos + 1);
		usleep(p_phil->time_to_eat * 1000);
		lfork(p_phil->forks, p_phil->pos, p_phil->phils_total, 0);
		rfork(p_phil->forks, p_phil->pos, 0);
	}
	else
	{
		rfork(p_phil->forks, p_phil->pos, 1);
		lfork(p_phil->forks, p_phil->pos, p_phil->phils_total, 1);
		p_phil->eat_stamp = get_time();
		atomic_status_prntr(MESSAGE_EAT, get_stamp(p_phil), p_phil->pos + 1);
		usleep(p_phil->time_to_eat * 1000);
		rfork(p_phil->forks, p_phil->pos, 0);
		lfork(p_phil->forks, p_phil->pos, p_phil->phils_total, 0);
	}

	return (1);
}