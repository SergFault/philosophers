/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:36:56 by Sergey            #+#    #+#             */
/*   Updated: 2021/11/30 01:33:54 by Sergey           ###   ########.fr       */
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
# define MESSAGE_TAKE "has taken a fork"
# define MESSAGE_EAT "is eating"
# define MESSAGE_SLEEP "is sleeping"
# define MESSAGE_THINK "is thinking"

enum{num_philo, time_to_die, time_to_eat, time_to_sleep, num_to_eat};

typedef struct s_phil_state
{
	int				phils_total;
	int				pos;
	int				start_t;
	int				is_alive;
	pthread_t		t;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_stamp;
	int				num_to_eat;
	int				eat_forever;
	pthread_mutex_t	*forks;
}				t_phil_state;

/* common utils */
int		ft_atoi(const char *nptr);
int		exit_fail(char *err, int status);
int		get_time(void);
void	atomic_status_prntr(char *message, int time_stamp, int phil_num);
/* base methods */
int		init(int argc, char *args[], t_phil_state **phil_st[]);
int		is_eat_forever(int num_to_eat);
int		update_status(t_phil_state *p_phil);
int		get_stamp(t_phil_state *p_phil);

#endif
