/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:36:56 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/20 16:20:15 by Sergey           ###   ########.fr       */
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
# include <semaphore.h>
# include <fcntl.h>
# include <sys/wait.h>

# define ERR_MALLOC "Error: allocation memory.\n"
# define ERR_ARGINT "Error: Args should be integers (Philos \
number <= 250 and > 0).\n"
# define ERR_ARGS "Error: Invalid args.\n"
# define ERR_PROC "Error: Process fork failed.\n"
# define ERR_SEM "Error: Semaphore.\n"
# define NUM_PARAM 5
# define MESSAGE_TAKE "has taken a fork"
# define MESSAGE_EAT "is eating"
# define MESSAGE_SLEEP "is sleeping"
# define MESSAGE_THINK "is thinking"
# define MESSAGE_DIE "died"
# define SMALL_SLEEP 1000

enum{num_philo, time_to_die, time_to_eat, time_to_sleep, num_to_eat};

typedef struct s_phil_state
{
	int				phils_total;
	int				pos;
	int				proc_id;
	unsigned long	start_t;
	int				is_alive;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	eat_stamp;
	int				num_to_eat;
	int				eat_forever;
	pthread_t		t;
	sem_t			*firts_line;
	sem_t			*second_line;
	sem_t			*third_line;
	sem_t			*atomic_sem;
	sem_t			*write_sem;
	sem_t			*forks;
	sem_t			*state_sem;
}				t_phil_state;

/* common utils */
int				process_fail(char *err, int status);
unsigned long	get_time(void);
void			atomic_status_prntr(char *message, t_phil_state *phil,
					int phil_num);
int				ft_atoi_err(const char *nptr, int *status);
int				contains_only_nums(const char *str);
void			precise_sleep(unsigned long u_sec);
/* base methods */
int				init(int argc, char *args[], t_phil_state **phil_st[]);
unsigned long	get_stamp(t_phil_state *p_phil);
int				eat(t_phil_state *p_phil);
void			free_resources(t_phil_state **phils);
void			wait_resources(t_phil_state **phils);
int				init_philos(t_phil_state **phil_st[], int params[]);
void			*check_dead(void *void_phil);
int				forks_init(int n, sem_t *sems[]);
int				philo_start(int n, t_phil_state **state);
#endif