/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:31:47 by Sergey            #+#    #+#             */
/*   Updated: 2021/11/30 01:23:10 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	is_eat_forever(int num_to_eat)
{
	if (num_to_eat == 0)
		return (1);
	return (0);
}

static pthread_mutex_t	*forks_init(int n)
{
	int				c;
	pthread_mutex_t	*forks;

	c = 0;
	forks = malloc(sizeof(pthread_mutex_t) * n); //todo check alloc
	while (c < n)
		pthread_mutex_init(&forks[c++], NULL);
}

static int	init_philos(t_phil_state **phil_st[], int params[])
{
	int				c;
	pthread_mutex_t	*forks;

	forks = forks_init(params[num_philo]);
	*phil_st = malloc(sizeof(t_phil_state *) * params[num_philo]); //todo check alloc
	c = 0;
	while (c < params[num_philo])
	{
		(*phil_st)[c] = malloc(sizeof(t_phil_state)); //todo check alloc and free
		(*phil_st)[0]->phils_total = params[num_philo];
		(*phil_st)[c]->forks = forks;
		(*phil_st)[c]->pos = c;
		(*phil_st)[c]->time_to_die = params[time_to_die];
		(*phil_st)[c]->time_to_eat = params[time_to_eat];
		(*phil_st)[c]->time_to_sleep = params[time_to_sleep];
		(*phil_st)[c]->is_alive = 1;
		if (params[num_to_eat] == 0)
			(*phil_st)[c]->eat_forever = 1;
		else
			(*phil_st)[c]->num_to_eat = params[num_to_eat];
		c++;
	}
	return (1);
}

int	init(int argc, char *argv[], t_phil_state **phil_st[])
{
	int	params[NUM_PARAM];

	if (argc < 5 || argc > 6)
		return (exit_fail("Invalid args.\n", -1));
	params[num_to_eat] = 0;
	params[num_philo] = ft_atoi(argv[1]);
	params[time_to_die] = ft_atoi(argv[2]);
	params[time_to_eat] = ft_atoi(argv[3]);
	params[time_to_sleep] = ft_atoi(argv[4]);
	if (argc == 6)
		params[num_to_eat] = ft_atoi(argv[5]);
	init_philos(phil_st, params);
	return (1);
}