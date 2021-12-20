/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 16:54:05 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/20 17:32:48 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static pthread_mutex_t	*forks_init(int n)
{
	int				c;
	pthread_mutex_t	*forks;

	c = 0;
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * n);
	if (!forks)
		return (process_fail_npt(ERR_MALLOC));
	while (c < n)
	{
		if (pthread_mutex_init(&forks[c++], NULL))
		{
			while (c-- >= 0)
				pthread_mutex_destroy(&forks[c++]);
			free(forks);
			return (process_fail_npt(ERR_MALLOC));
		}
	}
	return (forks);
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
				free(*phil_st[c]);
			free((*phil_st));
			return (process_fail(ERR_MALLOC, 1));
		}
		c++;
	}
	return (0);
}

static void	init_main_params(const int *params, t_phil_state **phil_st, int c)
{
	phil_st[c]->phils_total = params[num_philo];
	phil_st[c]->time_to_die = params[time_to_die];
	phil_st[c]->time_to_eat = params[time_to_eat];
	phil_st[c]->time_to_sleep = params[time_to_sleep];
}

static void	init_extra_mtxs(pthread_mutex_t	*extra[], t_phil_state **phil_st,
							int c)
{
	int	left_fork;
	int	right_fork;

	calculate_fork(phil_st[c], &left_fork, &right_fork);
	phil_st[c]->l_fork = &(phil_st[0]->forks)[left_fork];
	phil_st[c]->r_fork = &(phil_st[0]->forks)[right_fork];
	phil_st[c]->write = extra[0];
	phil_st[c]->line1 = extra[1];
	phil_st[c]->line2 = extra[2];
	phil_st[c]->line3 = extra[3];
}

static void	init_philos_params(int *params, t_phil_state **phil_st,
						pthread_mutex_t	*forks, pthread_mutex_t	*extra[])
{
	int	c;

	c = 0;
	while (c < params[num_philo])
	{
		init_main_params(params, phil_st, c);
		phil_st[c]->forks = forks;
		phil_st[c]->pos = c;
		init_extra_mtxs(extra, phil_st, c);
		phil_st[c]->is_alive = 1;
		phil_st[c]->eat_forever = 0;
		if (params[num_to_eat] == 0)
			phil_st[c]->eat_forever = 1;
		else
			phil_st[c]->num_to_eat = params[num_to_eat];
		phil_st[c]->can_b_free = 0;
		c++;
	}
}

int	init_extra_mtx(pthread_mutex_t *extra_mtxs[])
{
	int	c;
	int	n;

	n = 4;
	c = 0;
	while (c < n)
	{
		extra_mtxs[c] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!extra_mtxs[c])
			return (free_back((void **)extra_mtxs, c--));
		if (pthread_mutex_init(extra_mtxs[c], NULL))
		{
			while (c-- >= 0)
			{
				pthread_mutex_destroy(extra_mtxs[c]);
				free(extra_mtxs[c]);
			}
			return (process_fail(ERR_MTX, 1));
		}
		c++;
	}
	return (0);
}

int	init_philos(t_phil_state **phil_st[], int params[])
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	*extra_mtxs[4];

	forks = forks_init(params[num_philo]);
	if (!forks)
		return (1);
	if (init_extra_mtx(extra_mtxs))
	{
		free_forks(forks, (*phil_st)[0]->phils_total);
		return (1);
	}
	if (init_philos_alloc(phil_st, params[num_philo]))
	{
		free_extra_mtxs(extra_mtxs, params[num_philo]);
		free_forks(forks, (*phil_st)[0]->phils_total);
		return (1);
	}
	init_philos_params(params, *phil_st, forks, extra_mtxs);
	return (0);
}
