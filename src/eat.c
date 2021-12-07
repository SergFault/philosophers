/* ****************github.com/nafuka11/philosophers-visualizer********************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 01:06:12 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/07 13:08:21 by Sergey           ###   ########.fr       */
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
	if (take)
		pthread_mutex_lock(&forks[(pos + 2) % tot_phil]);
	else
		pthread_mutex_unlock(&forks[(pos + 2) % tot_phil]);
}

int	eat(t_phil_state *p_phil)
{
	if (p_phil->pos == p_phil->phils_total - 1)
	{
		lfork(p_phil->forks, p_phil->pos, p_phil->phils_total, 1);
		printf("Philo #%d, has taken fork %d\n", p_phil->pos + 1, (p_phil->pos + 2) % p_phil->phils_total); //todo delete
		rfork(p_phil->forks, p_phil->pos, 1);
		printf("Philo #%d, has taken fork %d\n", p_phil->pos + 1, p_phil->pos + 1); //todo delete
		atomic_status_prntr(MESSAGE_EAT, get_stamp(p_phil), p_phil->pos + 1);
		usleep(p_phil->time_to_eat);
		lfork(p_phil->forks, p_phil->pos, p_phil->phils_total, 0);
		printf("Philo #%d, has put fork %d\n", p_phil->pos + 1, (p_phil->pos + 2) % p_phil->phils_total); //todo delete
		rfork(p_phil->forks, p_phil->pos, 0);
		printf("Philo #%d, has put fork %d\n", p_phil->pos + 1, p_phil->pos + 1); //todo delete
	}
	else
	{
		rfork(p_phil->forks, p_phil->pos, 1);
		printf("Philo #%d, has taken fork %d\n", p_phil->pos + 1, p_phil->pos + 1); //todo delete
		lfork(p_phil->forks, p_phil->pos, p_phil->phils_total, 1);
		printf("Philo #%d, has taken fork %d\n", p_phil->pos + 1, p_phil->pos + 2); //todo delete
		atomic_status_prntr(MESSAGE_EAT, get_stamp(p_phil), p_phil->pos + 1);
		usleep(p_phil->time_to_eat);
		rfork(p_phil->forks, p_phil->pos, 0);
		printf("Philo #%d, has put fork %d\n", p_phil->pos + 1, p_phil->pos + 1); //todo delete
		lfork(p_phil->forks, p_phil->pos, p_phil->phils_total, 0);
		printf("Philo #%d, has put fork %d\n", p_phil->pos + 1, p_phil->pos + 2); //todo delete
	}

	return (1);
}