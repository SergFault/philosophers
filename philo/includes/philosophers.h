/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:36:56 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/20 23:36:58 by Sergey           ###   ########.fr       */
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

# define ERR_MALLOC "Error: allocation memory.\n"
# define ERR_ARGINT "Error: Args should be integers (Philos \
number <= 250 and > 0).\n"
# define ERR_ARGS "Error: Invalid args.\n"
# define ERR_THREAD "Error: Thread.\n"
# define ERR_MTX "Error: Mutex.\n"
# define NUM_PARAM 5
# define MESSAGE_TAKE "has taken a fork"
# define MESSAGE_EAT "is eating"
# define MESSAGE_SLEEP "is sleeping"
# define MESSAGE_THINK "is thinking"
# define MESSAGE_DIE "died"
# define SMALL_SLEEP 200

enum{num_philo, time_to_die, time_to_eat, time_to_sleep, num_to_eat};

typedef struct s_phil_state
{
	int				phils_total;
	int				pos;
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
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*write;
	pthread_mutex_t	*line1;
	pthread_mutex_t	*line2;
	pthread_mutex_t	*line3;
	int				can_b_free;
}				t_phil_state;

/* common utils */
int				process_fail(char *err, int status);
unsigned long	get_time(void);
void			atomic_status_prntr(char *message, t_phil_state *phil,
					int phil_num);
int				ft_atoi_err(const char *nptr, int *status);
void			*process_fail_npt(char *err);
int				contains_only_nums(const char *str);
void			precise_sleep(unsigned long u_sec);
/* base methods */
int				init(int argc, char *args[], t_phil_state **phil_st[]);
unsigned long	get_stamp(t_phil_state *p_phil);
void			init_stamp(void);
int				eat(t_phil_state *p_phil);
void			think(t_phil_state *p_phil);
void			init_stamps(t_phil_state *phils[], int total);
int				check_time(t_phil_state *phil);
void			free_resources(t_phil_state **phils, int n);
void			*philo_live(void *philo);
void			wait_resources(t_phil_state **phils);
void			check_philos(t_phil_state **phils, int n);
int				init_philos(t_phil_state **phil_st[], int params[]);
void			calculate_fork(t_phil_state *p_phil, int *first, int *second);
void			take_fork(pthread_mutex_t *forks, int fork, int take);
void			free_forks(pthread_mutex_t *forks, int n);
int				free_back(void *ptr[], int n);
void			free_extra_mtxs(pthread_mutex_t *mtxs[], int n);
void			atomic_status_prntr_dead(t_phil_state *phil, int phil_num);
#endif