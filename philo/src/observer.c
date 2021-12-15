/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 18:26:05 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/13 17:09:17 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	set_sleep(t_phil_state **phil_sts, int hungr)
{
	if (get_time() - phil_sts[hungr]->eat_stamp > phil_sts[0]->time_to_eat)
	{
		phil_sts[(hungr + 1) % (phil_sts[0]->phils_total)]->should_sleep = 1;
		if (hungr == 0)
		{
			phil_sts[phil_sts[0]->phils_total - 1]->should_sleep = 1;
		}
		else
		{
			phil_sts[hungr - 1]->should_sleep = 1;
		}
	}
}

static int	find_hungry(t_phil_state **ph_st, int *at_least_one)
{
	int				c;
	int				hungry_phil;
	unsigned long	max_stamp;

	c = 0;
	max_stamp = 0;
	*at_least_one = 0;
	hungry_phil = 0;
	while (c < ph_st[0]->phils_total)
	{
		if ((ph_st[c]->eat_forever || ph_st[c]->num_to_eat)
			&& ph_st[c]->is_alive)
		{
			*at_least_one = 1;
			if (max_stamp < get_time() - ph_st[c]->eat_stamp)
			{
				hungry_phil = c;
				max_stamp = get_time() - ph_st[c]->eat_stamp;
			}
			ph_st[c]->should_sleep = 0;
		}
		c++;
	}
	return (hungry_phil);
}

void	*waiter_routine(void *philos)
{
	t_phil_state	**phil_sts;
	int				at_least_one;
	int				hungry_phil;

	phil_sts = (t_phil_state **) philos;
	at_least_one = 1;
	while (at_least_one)
	{
		at_least_one = 0;
		hungry_phil = find_hungry(phil_sts, &at_least_one);
		set_sleep(phil_sts, hungry_phil);
		precise_sleep(5000);
	}
	return (NULL);
}
