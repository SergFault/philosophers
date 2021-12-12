/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:36:56 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/12 13:48:07 by Sergey           ###   ########.fr       */
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
# define MESSAGE_DIE "died"

enum{num_philo, time_to_die, time_to_eat, time_to_sleep, num_to_eat};

typedef struct s_phil_state
{
	int				phils_total;
	int				pos;
	int				should_sleep;
	unsigned long	start_t;
	int				is_alive;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	eat_stamp;
	int				num_to_eat;
	int				eat_forever;
	pthread_t		t;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*state_mtx;
	int				can_b_free;
}				t_phil_state;

/* common utils */
int				ft_atoi(const char *nptr);
int				exit_fail(char *err, int status);
unsigned long	get_time(void);
void			atomic_status_prntr(char *message, t_phil_state *phil,
					int phil_num);
/* base methods */
int				init(int argc, char *args[], t_phil_state **phil_st[]);
int				update_status(t_phil_state *p_phil);
unsigned long	get_stamp(t_phil_state *p_phil);
void			init_stamp(void);
int				eat(t_phil_state *p_phil);
void			phil_sleep(t_phil_state *p_phil);
void			think(t_phil_state *p_phil);
void			init_stamps(t_phil_state *phils[], int total);
void			*waiter_routine(void *philos);
int				check_time(t_phil_state *phil);

#endif
