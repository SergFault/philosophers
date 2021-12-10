/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 18:26:05 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/09 19:13:49 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*waiter_routine(void *philos)
{
	t_phil_state	**phil_sts;
	int				at_least_one;
	int				philos_num;
	int				hungry_phil;
	int				max_stamp;
	int				c;

	phil_sts = (t_phil_state **) philos;
	philos_num = phil_sts[0]->phils_total;
	at_least_one = 1;
	while (at_least_one)
	{
		c = 0;
		at_least_one = 0;
		max_stamp = 0;
		while (c < philos_num)
		{
			if (phil_sts[c]->eat_forever || phil_sts[c]->num_to_eat)
			{
				at_least_one = 1;
				if (max_stamp < get_time() - phil_sts[c]->eat_stamp)
				{
					hungry_phil = c;
					max_stamp = get_time() - phil_sts[c]->eat_stamp;
				}
				phil_sts[hungry_phil]->should_sleep = 0;
			}
			c++;
		}
		phil_sts[(hungry_phil + 1) % phil_sts[0]->phils_total]->should_sleep = 1;
		if (hungry_phil == 0)
			phil_sts[phil_sts[0]->phils_total - 1]->should_sleep = 1;
		else
			phil_sts[hungry_phil - 1]->should_sleep = 1;
		printf("Hungry phil #%d\n", hungry_phil + 1);
		usleep(phil_sts[0]->time_to_eat * 1000 / 3);
	}
}
