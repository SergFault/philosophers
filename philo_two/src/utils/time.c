/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 20:26:26 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/13 16:27:21 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	init_stamps(t_phil_state *phils[], int total)
{
	int				c;
	unsigned long	start_time;

	start_time = get_time();
	c = 0;
	while (c < total)
	{
		phils[c]->start_t = start_time;
		phils[c]->eat_stamp = start_time;
		c++;
	}
}

unsigned long	get_stamp(t_phil_state *p_phil)
{
	return (get_time() - p_phil->start_t);
}
