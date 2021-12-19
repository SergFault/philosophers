/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 18:21:12 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/19 15:11:20 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	free_resources(t_phil_state **phils, int n)
{
	int	c;

	c = 0;
	if (phils)
	{
		if (phils[0]->forks)
			sem_close(phils[0]->forks);
		c = 0;
		while (c < n)
			free(phils[c++]);
		free(phils);
	}
}
