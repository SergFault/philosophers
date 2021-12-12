/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 18:21:12 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/12 19:04:03 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	free_resources(t_phil_state **phils, int n)
{
	int	c;

	c = 0;
	if (phils && *phils)
	{
		pthread_mutex_destroy(phils[0]->state_mtx);
		free(phils[0]->state_mtx);
	}
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