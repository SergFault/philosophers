/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 23:42:36 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/20 23:48:00 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

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

void	init_extra_mtxs(pthread_mutex_t	*extra[], t_phil_state **phil_st,
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

pthread_mutex_t	*forks_init(int n)
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
