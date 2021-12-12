/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 20:57:05 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/11 13:18:33 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	atomic_status_prntr(char *message, t_phil_state *phil, int phil_num)
{
	static pthread_mutex_t	print_mutex = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&print_mutex);
	printf("%lu %d %s\n", get_stamp(phil), phil_num, message);
	pthread_mutex_unlock(&print_mutex);
}
