/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:49:36 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/20 00:18:42 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*philo_live(void *philo)
{
	t_phil_state	*phil;

	phil = ((t_phil_state *) philo);
	pthread_create(&phil->t, NULL, check_dead, philo);
	while ((phil->num_to_eat || phil->eat_forever) && phil->is_alive)
	{
		eat(phil);
		if (phil->num_to_eat <= 0 && phil->eat_forever == 0)
			break ;
		sem_wait(phil->state_sem);
		atomic_status_prntr(MESSAGE_SLEEP, phil, phil->pos + 1);
		sem_post(phil->state_sem);
		precise_sleep(phil->time_to_sleep * 1000);
		sem_wait(phil->state_sem);
		atomic_status_prntr(MESSAGE_THINK, phil, phil->pos + 1);
		sem_post(phil->state_sem);
		precise_sleep(phil->time_to_eat * 1000);
	}
	pthread_join(phil->t, NULL);
	if (!phil->is_alive)
	{
		exit(1);
	}
	exit(0);
}
