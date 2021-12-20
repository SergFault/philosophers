/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 16:54:05 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/20 15:25:06 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	init_philos_alloc(t_phil_state **phil_st[], int n)
{
	int	c;

	*phil_st = (t_phil_state **)malloc(sizeof(t_phil_state *) * n);
	if (!(*phil_st))
		return (1);
	c = 0;
	while (c < n)
	{
		(*phil_st)[c] = (t_phil_state *)malloc(sizeof(t_phil_state));
		if (!(*phil_st)[c])
		{
			while (--c >= 0)
				free(*phil_st[c]);
			free((*phil_st));
			return (process_fail(ERR_MALLOC, 1));
		}
		c++;
	}
	return (0);
}

static void	put_sems(t_phil_state *phil_st, sem_t *sems[])
{
	phil_st->forks = sems[0];
	phil_st->state_sem = sems[1];
	phil_st->write_sem = sems[2];
	phil_st->atomic_sem = sems[3];
	phil_st->firts_line = sems[4];
	phil_st->second_line = sems[5];
	phil_st->third_line = sems[6];
}

static void	init_philos_params(const int *params, t_phil_state **phil_st,
									sem_t *sems[])
{
	int	c;

	c = 0;
	while (c < params[num_philo])
	{
		put_sems(phil_st[c], sems);
		phil_st[c]->phils_total = params[num_philo];
		phil_st[c]->pos = c;
		phil_st[c]->time_to_die = params[time_to_die];
		phil_st[c]->time_to_eat = params[time_to_eat];
		phil_st[c]->time_to_sleep = params[time_to_sleep];
		phil_st[c]->is_alive = 1;
		phil_st[c]->eat_forever = 0;
		phil_st[c]->num_to_eat = params[num_to_eat];
		if (params[num_to_eat] == 0)
			phil_st[c]->eat_forever = 1;
		else
			phil_st[c]->num_to_eat = params[num_to_eat];
		c++;
	}
}

int	init_philos(t_phil_state **phil_st[], int params[])
{
	sem_t	*sems[7];

	if (forks_init(params[num_philo], sems))
		return (1);
	if (init_philos_alloc(phil_st, params[num_philo]))
		return (1);
	init_philos_params(params, *phil_st, sems);
	return (0);
}
