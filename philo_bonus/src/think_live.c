/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:49:36 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/20 16:19:42 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	philo_live(void *philo)
{
	t_phil_state	*phil;

	phil = ((t_phil_state *) philo);
	if (phil->pos % 2)
		precise_sleep(500);
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
	}
	pthread_join(phil->t, NULL);
	if (!phil->is_alive)
	{
		return (1);
	}
	return (0);
}

int	philo_start(int n, t_phil_state **state)
{
	int	status;

	status = philo_live(state[n]);
	free_resources(state);
	exit(status);
}
