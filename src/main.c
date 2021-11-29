/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:29:09 by Sergey            #+#    #+#             */
/*   Updated: 2021/11/30 00:37:28 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/philosophers.h"

void	*philo_live(void *philo)
{
	t_phil_state	*phil;
	int				eat_forever;

	phil = ((t_phil_state *) philo);
	phil->start_t = get_time();
	while (phil->num_to_eat || phil->eat_forever)
	{
		atomic_status_prntr(MESSAGE_TAKE, get_time() - phil->start_t,
			phil->pos);
		if (!phil->eat_forever)
			phil->num_to_eat--;
	}
}

void	check_philos(t_phil_state **phils, int n)
{
	int	at_least_one;
	int	;
	int	c;

	at_least_one = 1;
	while(at_least_one)
	{
		c = 0;
		at_least_one = 0;
		while(c < n)
		{
			if (phils[c]->num_to_eat || phils[c]->eat_forever)
				at_least_one = 1;
			c++;
		}
	}
}

int	main(int argc, char *argv[]){
	t_tot_state	tot_state;
	t_phil_state	**phils;
	int				i;

	if (!init(argc, argv, &tot_state, &phils))
		return (-1);
	i = 0;
	while (i < tot_state.philos_num)
	{
		pthread_create(&phils[i]->t, NULL, philo_live, phils[i]);
		pthread_detach(phils[i]->t);
		i++;
	}
	check_philos(phils, tot_state.philos_num);
	/*while (i < tot_state.philos_num)
	{
		printf("Philosopher #%d\n", (phils[i])->pos);
		printf("time_to_die : %d\n", (phils[i])->time_to_die);
		printf("time_to_eat : %d\n", (phils[i])->time_to_eat);
		printf("time_to_sleep : %d\n", (phils[i])->time_to_sleep);
		printf("num_to_eat : %d\n\n", (phils[i])->num_to_eat);
		i++;
	}*/
	printf("Main returns.\n");
}
