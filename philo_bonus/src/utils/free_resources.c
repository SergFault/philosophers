/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 18:21:12 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/20 15:54:22 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	free_sems(t_phil_state **phils)
{
	sem_close(phils[0]->forks);
	sem_close(phils[0]->state_sem);
	sem_close(phils[0]->write_sem);
	sem_close(phils[0]->atomic_sem);
	sem_close(phils[0]->firts_line);
	sem_close(phils[0]->second_line);
	sem_close(phils[0]->third_line);
}

void	free_resources(t_phil_state **phils)
{
	int	c;
	int	n;

	if (phils)
	{
		free_sems(phils);
		c = 0;
		n = phils[0]->phils_total;
		while (c < n)
			free(phils[c++]);
		free(phils);
	}
}
