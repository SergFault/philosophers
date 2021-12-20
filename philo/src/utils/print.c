/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 20:57:05 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/13 15:30:11 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

static int	is_die_message(const char *message)
{
	const char	*die = MESSAGE_DIE;
	int			c;

	c = 0;
	while (message[c] && die[c])
	{
		if (message[c] != die[c])
			return (0);
		c++;
	}
	return (1);
}

void	atomic_status_prntr(char *message, t_phil_state *phil, int phil_num)
{
	pthread_mutex_lock(phil->write);
	if ((phil->is_alive && check_time(phil)) || is_die_message(message))
		printf("%lu %d %s\n", get_stamp(phil), phil_num, message);
	pthread_mutex_unlock(phil->write);
}
