/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:29:09 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/12 19:16:47 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*philo_live(void *philo)
{
	t_phil_state	*phil;

	phil = ((t_phil_state *) philo);
	if (phil->pos % 2)
		usleep(1000);
	while ((phil->num_to_eat || phil->eat_forever) && phil->is_alive)
	{
		eat(phil);
		think(phil);
	}
	phil->can_b_free = 1;
	return (NULL);
}

void	set_all_dead(t_phil_state **phils)
{
	int	c;

	c = 0;
	while (c < phils[0]->phils_total)
	{
		phils[c++]->is_alive = 0;
	}
}

int	check_time(t_phil_state *phil)
{
	if (get_time() - phil->eat_stamp >= phil->time_to_die)
		return (0);
	return (1);
}

int	check_dead(t_phil_state **phils, int pos)
{
	pthread_mutex_lock(phils[pos]->state_mtx);
	if (get_time() - phils[pos]->eat_stamp >= phils[pos]->time_to_die)
	{
		phils[pos]->is_alive = 0;
		set_all_dead(phils);
		atomic_status_prntr(MESSAGE_DIE, phils[pos], phils[pos]->pos + 1);
		pthread_mutex_unlock(phils[pos]->state_mtx);
		return (1);
	}
	pthread_mutex_unlock(phils[pos]->state_mtx);
	return (0);
}

void	wait_resources(t_phil_state **phils)
{
	int	c;
	int	should_wait;

	c = 0;
	should_wait = 1;
	while (should_wait)
	{
		should_wait = 0;
		c = 0;
		while (c < phils[0]->phils_total)
		{
			if (phils[c]->can_b_free == 0)
				should_wait = 1;
			c++;
		}
		if (should_wait == 0)
			return ;
		usleep(1000);
	}
}

void	check_philos(t_phil_state **phils, int n)
{
	int	at_least_one;
	int	c;

	at_least_one = 1;
	while (at_least_one)
	{
		c = 0;
		at_least_one = 0;
		while (c < n)
		{
			if (phils[c]->num_to_eat || phils[c]->eat_forever)
			{
				at_least_one = 1;
				if (check_dead(phils, c))
				{
					wait_resources(phils);
					return ;
				}
			}
			c++;
		}
	}
}

int	main(int argc, char *argv[])
{
	t_phil_state	**phils;
	pthread_t		obs;
	int				i;

	if (init(argc, argv, &phils) == 1)
		return (1);
	i = 0;
	init_stamps(phils, phils[0]->phils_total);
	while (i < (*phils)[0].phils_total)
	{
		pthread_create(&phils[i]->t, NULL, philo_live, phils[i]);
		pthread_detach(phils[i]->t);
		i++;
	}
	pthread_create(&obs, NULL, waiter_routine, phils);
	check_philos(phils, (*phils)[0].phils_total);
	usleep(1000);
	pthread_join(obs, NULL);
	free_resources(phils, phils[0]->phils_total);
	return (0);
}
