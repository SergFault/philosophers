/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:36:56 by Sergey            #+#    #+#             */
/*   Updated: 2021/11/29 20:46:08 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <limits.h>
# include <sys/time.h>
# include <unistd.h>

# define NUM_PARAM 5

enum{num_philo, time_to_die, time_to_eat, time_to_sleep, num_to_eat};

typedef struct s_total_state
{
	int	philos_num;
}				t_tot_state;

typedef struct s_phil_state
{
	int			pos;
	int			start_t;
	pthread_t	t;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			num_to_eat;
}				t_phil_state;

/* common utils */
int	ft_atoi(const char *nptr);
int	exit_fail(char *err, int status);
int	get_time(void);
/* base methods */
int	init(int argc, char *args[], t_tot_state *tot_st, t_phil_state **phil_st[]);
int	is_eat_forever(int num_to_eat);

#endif
