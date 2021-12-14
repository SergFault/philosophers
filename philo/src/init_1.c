/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 16:54:05 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/13 17:04:45 by Sergey           ###   ########.fr       */
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

static void	init_philos_params(int *params, t_phil_state **phil_st,
									pthread_mutex_t	*forks)
{
	int	c;

	c = 0;
	while (c < params[num_philo])
	{
		phil_st[c]->phils_total = params[num_philo];
		phil_st[c]->forks = forks;
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
		phil_st[c]->should_sleep = 0;
		phil_st[c]->can_b_free = 0;
		c++;
	}
}

int	init_philos(t_phil_state **phil_st[], int params[])
{
	pthread_mutex_t	*forks;

	forks = forks_init(params[num_philo]);
	if (!forks)
		return (1);
	if (init_philos_alloc(phil_st, params[num_philo]))
		return (1);
	init_philos_params(params, *phil_st, forks);
	return (0);
}
