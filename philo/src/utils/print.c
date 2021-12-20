/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 20:57:05 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/20 23:36:58 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	atomic_status_prntr(char *message, t_phil_state *phil, int phil_num)
{
	pthread_mutex_lock(phil->write);
	if (phil->is_alive)
		printf("%lu %d %s\n", get_stamp(phil), phil_num, message);
	pthread_mutex_unlock(phil->write);
}

void	atomic_status_prntr_dead(t_phil_state *phil, int phil_num)
{
	pthread_mutex_lock(phil->write);
	if (phil->is_alive)
		printf("%lu %d %s\n", get_stamp(phil), phil_num, MESSAGE_DIE);
}
