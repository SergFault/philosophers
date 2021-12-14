/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 01:27:15 by Sergey            #+#    #+#             */
/*   Updated: 2021/11/30 01:33:54 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	update_status(t_phil_state *p_phil)
{
	if (get_time() - p_phil->eat_stamp >= p_phil->eat_stamp)
	{
		p_phil->is_alive = 0;
		return (0);
	}
	else
		return (1);
}
