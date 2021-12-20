/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 18:21:12 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/20 23:37:01 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	free_resources(t_phil_state **phils, int n)
{
	int	c;

	c = 0;
	pthread_mutex_destroy(phils[0]->state_mtx);
	pthread_mutex_destroy(phils[0]->write);
	pthread_mutex_destroy(phils[0]->line1);
	pthread_mutex_destroy(phils[0]->line2);
	pthread_mutex_destroy(phils[0]->line3);
	free(phils[0]->state_mtx);
	free(phils[0]->write);
	free(phils[0]->line1);
	free(phils[0]->line2);
	free(phils[0]->line3);
	while (c < n)
	{
		pthread_mutex_destroy(&(phils[0]->forks[c]));
		c++;
	}
	free(phils[0]->forks);
	c = 0;
	while (c < n)
		free(phils[c++]);
	free(phils);
}

int	free_back(void *ptr[], int n)
{
	while (n >= 0)
		free(ptr[n--]);
	return (1);
}

void	free_forks(pthread_mutex_t *forks, int n)
{
	int	c;

	c = 0;
	while (c < n)
		pthread_mutex_destroy(&forks[c++]);
	free(forks);
}

void	free_extra_mtxs(pthread_mutex_t *mtxs[], int n)
{
	int	c;

	c = 0;
	while (c < n)
		pthread_mutex_destroy(mtxs[c++]);
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
