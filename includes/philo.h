/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 01:19:17 by user42            #+#    #+#             */
/*   Updated: 2021/08/23 10:54:13 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define NUMX 10
typedef struct s_philo
{
	int			num;
	int			teste;
	int			status;
	int			fork_left;
	int			fork_right;
	long long	t_eat;
	long long	t_sleep;
	long long	t_die;
	pthread_t	id;
}				t_philo;

typedef struct s_all
{
	int					argc;
	char				**argv;
	int					posic;
	int					qtt_philo;
	int					qtt_eat;
	int					ini;
	int					curr;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	long long			init_time;
	int					dead;
	int					n_eat;
	t_philo				*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		write;
	pthread_t			tim;
}				t_all;

long		ft_atoi(const char *str);
int			verify_args(t_all *all, int j);
int			get_info(t_all *all);
int			create_philos(t_all *all, int i, int next);
int			restore_times(t_all *all, int i);
long long	get_time(void);
int			diff_time(long long last);
void		*timming(void *arg);
void		*action(void *arg);
void		create_thread(t_all *all);
void		print_action(char *action, t_all *all, int i, int num);
int			wait_action(t_all *all, long long time);
void		do_action(t_all *all, int i);
void		end_threads(t_all *all);
void		drop_forks(t_all *all);

#endif
