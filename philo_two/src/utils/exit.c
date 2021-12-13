/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:46:19 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/13 14:19:43 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	*process_fail_npt(char *err)
{
	while (*err)
		write(2, err++, 1);
	return (NULL);
}

int	process_fail(char *err, int status)
{
	while (*err)
		write(2, err++, 1);
	return (status);
}
