/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 20:57:05 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/19 23:07:18 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	atomic_status_prntr(char *message, t_phil_state *phil, int phil_num)
{
	sem_wait(phil->write_sem);
	if (phil->is_alive)
		printf("%lu %d %s\n", get_stamp(phil), phil_num, message);
	sem_post(phil->write_sem);
}
