/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:59:58 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/20 15:26:50 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	is_sems_ok(sem_t *sems[])
{
	if (sems[0] != SEM_FAILED)
		sem_unlink("/forks-sem");
	if (sems[1] != SEM_FAILED)
		sem_unlink("/write-sem");
	if (sems[2] != SEM_FAILED)
		sem_unlink("/state-sem");
	if (sems[3] != SEM_FAILED)
		sem_unlink("/atomic-sem");
	if (sems[4] != SEM_FAILED)
		sem_unlink("/first-sem");
	if (sems[5] != SEM_FAILED)
		sem_unlink("/second-sem");
	if (sems[5] != SEM_FAILED)
		sem_unlink("/third-sem");
	if (sems[0] == SEM_FAILED || sems[1] == SEM_FAILED || sems[2] == SEM_FAILED
		|| sems[3] == SEM_FAILED || sems[4] == SEM_FAILED
		|| sems[5] == SEM_FAILED || sems[6] == SEM_FAILED)
		return ((process_fail(ERR_SEM, 0)));
	return (1);
}

int	forks_init(int n, sem_t *sems[])
{
	sems[0] = sem_open("/forks-sem", O_CREAT | O_EXCL, 0, n);
	sems[1] = sem_open("/state-sem", O_CREAT | O_EXCL, 0, 1);
	sems[2] = sem_open("/write-sem", O_CREAT | O_EXCL, 0, 1);
	sems[3] = sem_open("/atomic-sem", O_CREAT | O_EXCL, 0, 1);
	sems[4] = sem_open("/first-sem", O_CREAT | O_EXCL, 0, 1);
	sems[5] = sem_open("/second-sem", O_CREAT | O_EXCL, 0, 1);
	sems[6] = sem_open("/third-sem", O_CREAT | O_EXCL, 0, 1);
	if (is_sems_ok(sems))
		return (0);
	return (1);
}
