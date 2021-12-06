/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:29:09 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/06 20:28:34 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*philo_live(void *philo)
{
	t_phil_state	*phil;

	phil = ((t_phil_state *) philo);
	phil->start_t = get_time();
	while (phil->num_to_eat || phil->eat_forever)
	{
		eat(phil);
	}
}

void	check_philos(t_phil_state **phils, int n)
{
	int	at_least_one;
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
	t_phil_state	**phils;
	int				i;

	if (!init(argc, argv, &phils))
		return (1);
	i = 0;
	init_stamp();
	while (i < (*phils)[0].phils_total)
	{
		pthread_create(&phils[i]->t, NULL, philo_live, phils[i]);
		pthread_detach(phils[i]->t);
		i++;
	}
	check_philos(phils, (*phils)[0].phils_total);
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
