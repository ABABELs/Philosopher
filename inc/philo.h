/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabel <aabel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 10:59:57 by arthurabel        #+#    #+#             */
/*   Updated: 2023/06/29 15:55:32 by aabel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define ALLOC_ERROR_1 "ERROR WHILE ALLOCATING THREADS IDs"
# define ALLOC_ERROR_3 "ERROR WHILE ALLOCATING PHILOS"
# define ALLOC_ERROR_2 "ERROR WHILE ALLOCATING FORKS"

# define ERROR_IN_1 "INVALID INPUT CHARACTER"
# define ERROR_IN_2 "INVALID INPUT VALUES"

# define TH_ERROR "ERROR WHILE CREATING THREADS"
# define JOIN_ERR "ERROR WHILE JOINING THREADS"
# define INIT_ERR_1 "ERROR WHILE INIT FORKS"

# define TAKE_FORKS "has taken a fork"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"
# define EATING "is eating"
# define DIED "died"

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		t1;
	int				id;
	int				eat_cont;
	int				status;
	int				eating;
	uint64_t		time_to_die;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}t_philo;

typedef struct s_data
{
	pthread_t		*tid;
	int				philo_num;
	int				meals_nb;
	int				dead;
	int				finished;
	t_philo			*philos;
	u_int64_t		death_time;
	u_int64_t		eat_time;
	u_int64_t		sleep_time;
	u_int64_t		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
}	t_data;

int		init(t_data *data, char **argv, int argc);
int		init_philos(t_data *data);
int		init_data(t_data *data, char **argv, int argc);
int		init_forks(t_data *data);
int		alloc(t_data *data);
int		ft_usleep(useconds_t time);
void	ft_exit(t_data *data);
void	clear_data(t_data *data);
int		one_philo(t_data *data);
int		error(char *str, t_data *data);
int		thread_init(t_data *data);
void	*routine(void *philo_pointer);
void	*supervisor(void *philo_pointer);
void	*monitor(void *data_pointer);

#endif
