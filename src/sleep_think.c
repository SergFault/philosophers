/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:49:36 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/07 15:12:33 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	phil_sleep(t_phil_state *p_phil)
{
	atomic_status_prntr(MESSAGE_SLEEP, get_stamp(p_phil), p_phil->pos + 1);
	usleep(p_phil->time_to_sleep * 1000);
}

void	think(t_phil_state *p_phil)
{
	atomic_status_prntr(MESSAGE_THINK, get_stamp(p_phil), p_phil->pos + 1);
}