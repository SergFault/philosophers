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

void	take_fork(pthread_mutex_t *forks, int fork, int take)
{
	if (take)
		pthread_mutex_lock(&forks[fork]);
	else
		pthread_mutex_unlock(&forks[fork]);
}

void	calculate_fork(t_phil_state *p_phil, int *first, int *second)
{
	if (p_phil->pos == p_phil->phils_total - 1)
	{
		*first = (p_phil->pos + 1) % p_phil->phils_total;
		*second = p_phil->pos;
	}
	else
	{
		*first = p_phil->pos;
		*second = (p_phil->pos + 1) % p_phil->phils_total;
	}
}

void	put_forks(t_phil_state *p_phil)
{
	int	first;
	int	second;

	calculate_fork(p_phil, &first, &second);
	take_fork(p_phil->forks, first, 0);
	take_fork(p_phil->forks, second, 0);
}
