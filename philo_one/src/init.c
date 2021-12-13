/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:31:47 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/13 15:25:24 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static pthread_mutex_t	*forks_init(int n)
{
	int				c;
	pthread_mutex_t	*forks;

	c = 0;
	forks = malloc(sizeof(pthread_mutex_t) * n); //todo check alloc
	while (c < n)
		pthread_mutex_init(&forks[c++], NULL);
	return forks;
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
			return (process_fail("Memory allocation error.\n", 1));
		}
		c++;
	}
	return (0);
}

static int	init_philos(t_phil_state **phil_st[], int params[])
{
	int				c;
	pthread_mutex_t	*forks;

	forks = forks_init(params[num_philo]);
	if (init_philos_alloc(phil_st, params[num_philo]))
		return (1);
	c = 0;
	while (c < params[num_philo])
	{
		(*phil_st)[c]->phils_total = params[num_philo];
		(*phil_st)[c]->forks = forks;
		(*phil_st)[c]->pos = c;
		(*phil_st)[c]->time_to_die = params[time_to_die];
		(*phil_st)[c]->time_to_eat = params[time_to_eat];
		(*phil_st)[c]->time_to_sleep = params[time_to_sleep];
		(*phil_st)[c]->is_alive = 1;
		(*phil_st)[c]->eat_forever = 0;
		(*phil_st)[c]->num_to_eat = params[num_to_eat];
		if (params[num_to_eat] == 0)
			(*phil_st)[c]->eat_forever = 1;
		else
			(*phil_st)[c]->num_to_eat = params[num_to_eat];
		(*phil_st)[c]->should_sleep = 0;
		(*phil_st)[c]->can_b_free = 0;
		c++;
	}
	return (0);
}

int	init_state_mtx(t_phil_state *phils[], int c)
{
	int					i;
	pthread_mutex_t		*p_state_mtx;

	i = 0;
	p_state_mtx = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!(p_state_mtx))
		return (0);
	pthread_mutex_init(p_state_mtx, NULL);
	while (i < c)
		phils[i++]->state_mtx = p_state_mtx; //todo malloc
	return (1);
}

static int	contains_only_nums(const char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

static int	validate_args(int argc, char *argv[])
{
	int	c;

	if (argc < 5 || argc > 6)
		return (process_fail("Invalid args.\n", 1));
	c = 1;
	while (c < argc)
	{
		if (!contains_only_nums(argv[c++]))
		{
			return (process_fail("Args should be integers.\n", 1));
		}
	}
	return (0);
}

static int	get_params(int argc, char *argv[], int params[])
{
	int	status;

	status = 0;
	params[num_to_eat] = 0;
	params[num_philo] = ft_atoi_err(argv[1], &status);
	params[time_to_die] = ft_atoi_err(argv[2], &status);
	params[time_to_eat] = ft_atoi_err(argv[3], &status);
	params[time_to_sleep] = ft_atoi_err(argv[4], &status);
	if (argc == 6)
		params[num_to_eat] = ft_atoi_err(argv[5], &status);
	if (status || params[num_philo] > 250)
		return (process_fail("Invalid arguments values\n", 1));
	return (0);
}

int	init(int argc, char *argv[], t_phil_state **phil_st[])
{
	int	params[NUM_PARAM];

	if (validate_args(argc, argv))
		return (1);
	if (get_params(argc, argv, params))
		return (1);
	if (init_philos(phil_st, params))
		return (1);
	init_state_mtx(*phil_st, params[num_philo]);
	return (0);
}