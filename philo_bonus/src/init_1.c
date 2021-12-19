/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 16:54:05 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/20 00:44:14 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	forks_init(int n, sem_t *sems[])
{
	sems[0] = sem_open("/forks-sem", O_CREAT | O_EXCL, 0, n);
	sems[1] = sem_open("/state-sem", O_CREAT | O_EXCL, 0, 1);
	sems[2] = sem_open("/write-sem", O_CREAT | O_EXCL, 0, 1);
	sems[3] = sem_open("/atomic-sem", O_CREAT | O_EXCL, 0, 1);

	sems[4] = sem_open("/first-sem", O_CREAT | O_EXCL, 0, 1);
	sems[5] = sem_open("/second-sem", O_CREAT | O_EXCL, 0, 1);
	sems[6] = sem_open("/third-sem", O_CREAT | O_EXCL, 0, 1);

	sem_unlink("/forks-sem");
	sem_unlink("/write-sem");
	sem_unlink("/state-sem");
	sem_unlink("/atomic-sem");

	sem_unlink("/first-sem");
	sem_unlink("/second-sem");
	sem_unlink("/third-sem");

	if (sems[0] == SEM_FAILED || sems[1] == SEM_FAILED || sems[2] == SEM_FAILED
		|| sems[3] == SEM_FAILED)
		return (0);
	return (1);
}

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
			{
				free(*phil_st[c]);
			}
			free((*phil_st));
			return (process_fail(ERR_MALLOC, 1));
		}
		c++;
	}
	return (0);
}

static void	init_philos_params(const int *params, t_phil_state **phil_st,
									sem_t *sems[])
{
	int	c;

	c = 0;
	while (c < params[num_philo])
	{
		phil_st[c]->phils_total = params[num_philo];
		phil_st[c]->forks = sems[0];
		phil_st[c]->state_sem = sems[1];
		phil_st[c]->write_sem = sems[2];
		phil_st[c]->atomic_sem = sems[3];

		phil_st[c]->firts_line = sems[4];
		phil_st[c]->second_line = sems[5];
		phil_st[c]->third_line = sems[6];


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

	forks_init(params[num_philo], sems);
	if (init_philos_alloc(phil_st, params[num_philo]))
		return (1);
	init_philos_params(params, *phil_st, sems);
	return (0);
}
