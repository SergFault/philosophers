/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:49:36 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/20 14:46:22 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philosophers.h"

int	eat(t_phil_state *p_phil)
{
	sem_wait(p_phil->firts_line);
	sem_wait(p_phil->second_line);
	sem_post(p_phil->firts_line);
	sem_wait(p_phil->third_line);
	usleep(100);
	sem_post(p_phil->second_line);
	sem_wait(p_phil->atomic_sem);
	sem_post(p_phil->third_line);
	sem_wait(p_phil->forks);
	atomic_status_prntr(MESSAGE_TAKE, p_phil, p_phil->pos + 1);
	sem_wait(p_phil->forks);
	atomic_status_prntr(MESSAGE_TAKE, p_phil, p_phil->pos + 1);
	sem_post(p_phil->atomic_sem);
	sem_wait(p_phil->state_sem);
	atomic_status_prntr(MESSAGE_EAT, p_phil, p_phil->pos + 1);
	p_phil->eat_stamp = get_time();
	sem_post(p_phil->state_sem);
	precise_sleep(p_phil->time_to_eat * 1000);
	if (p_phil->num_to_eat > 0)
		p_phil->num_to_eat--;
	sem_post(p_phil->forks);
	sem_post(p_phil->forks);
	return (1);
}
