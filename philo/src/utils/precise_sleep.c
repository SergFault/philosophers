/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precise_sleep.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:00:36 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/15 15:15:26 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	precise_sleep(unsigned long u_sec)
{
	unsigned long	start_t;

	start_t = get_time() * 1000;
	while (get_time() * 1000 - start_t < u_sec)
		usleep(SMALL_SLEEP);
}
