/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 16:43:02 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/20 01:13:56 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	check_time(t_phil_state *phil)
{
	if (get_time() - phil->eat_stamp >= phil->time_to_die)
		return (0);
	return (1);
}

void	*check_dead(void *void_phil)
{
	t_phil_state	*phil;

	phil = (t_phil_state *)void_phil;
	while (1)
	{
		sem_wait(phil->state_sem);
		if (get_time() - phil->eat_stamp >= phil->time_to_die)
		{
			atomic_status_prntr(MESSAGE_DIE, phil, phil->pos + 1);
			phil->is_alive = 0;
			sem_wait(phil->write_sem);
			exit(1);
		}
		sem_post(phil->state_sem);
		if (phil->num_to_eat <= 0 && phil->eat_forever == 0)
			break ;
		usleep(1000);
	}
	return (NULL);
}
