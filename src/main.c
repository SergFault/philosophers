/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:29:09 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/09 19:39:07 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*philo_live(void *philo)
{
	t_phil_state	*phil;

	phil = ((t_phil_state *) philo);
	while (phil->num_to_eat || phil->eat_forever)
	{
		eat(phil);
		printf("%d num to eat %d\n", phil->pos + 1, phil->num_to_eat);
		phil_sleep(phil);
		think(phil);
	}
	return NULL;
}

void	set_all_dead(t_phil_state **phils, int pos)
{
	int	c;

	c = 0;
	while (c < phils[0]->phils_total)
	{
		phils[c++]->is_alive = 0;
	}
}

int	check_dead(t_phil_state **phils, int pos)
{
	pthread_mutex_lock(phils[0]->state_mtx);
	if (get_time() - phils[pos]->eat_stamp >= phils[pos]->time_to_die)
	{
		phils[pos]->is_alive = 0;
		atomic_status_prntr(MESSAGE_DIE, get_time() - phils[pos]->start_t,
			phils[pos]->pos + 1);
		printf("stamp last eat: %lu now: %lu diff: %lu\n", phils[pos]->eat_stamp, get_time(), get_time() - phils[pos]->eat_stamp);
		set_all_dead(phils, pos);
		return (1);
	}
	pthread_mutex_unlock(phils[0]->state_mtx);
	return (0);
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
					return ;
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

	if (!init(argc, argv, &phils))
		return (-1);
	i = 0;
	init_stamps(phils, phils[0]->phils_total);
	while (i < (*phils)[0].phils_total)
	{
		pthread_create(&phils[i]->t, NULL, philo_live, phils[i]);
		pthread_detach(phils[i]->t);
		i++;
	}
	pthread_create(&obs, NULL, waiter_routine, phils);
	pthread_detach(obs);
	check_philos(phils, (*phils)[0].phils_total);
	printf("Main returns.\n");
}
