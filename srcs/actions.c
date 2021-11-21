/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 17:33:52 by cpereira          #+#    #+#             */
/*   Updated: 2021/11/21 15:48:14 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// arrumar erro de ./philo 4 110 200 200

#include "philo.h"

void	*timming(void *arg)
{
	int		i;
	t_all	*all;

	all = (t_all *)arg;
	while (!all->dead && (all->n_eat < all->qtt_eat || all->qtt_eat == -1))
	{
		i = 0;
		while (i < all->qtt_philo && all->dead != 1)
		{
			if (diff_time(all->philos[i].t_die) > all->time_die)
			{
				print_action("\033[1;31m died \033[1;37m", all,
					all->philos[i].num, -1);
				all->dead = 1;
				pthread_mutex_lock(&(all->write));
				drop_forks(all);
			}
			i++;
		}
	}
	drop_forks(all);
	end_threads(all);
	return (NULL);
}

void	print_action(char *action, t_all *all, int i, int num)
{
	if (all->dead == 0)
	{
		pthread_mutex_lock(&(all->write));
		if (num >= 0)
			printf("%dms Philo %d %s %d\n", diff_time(all->init_time),
				i, action, num);
		else
			printf("%dms Philo %d %s\n", diff_time(all->init_time), i, action);
		pthread_mutex_unlock(&(all->write));
	}
}

void	*action(void *arg)
{
	int		i;
	t_all	*all;

	all = (t_all *)arg;
	i = all->curr;
	all->dead = 0;
	all->philos[i].status = 0;
	all->init_time = get_time();
	while (!all->dead && (all->n_eat < all->qtt_eat || all->qtt_eat == -1))
	{
		if (all->philos[i].status == 0)
			do_action(all, i);
		usleep(50);
	}
	return (NULL);
}

void	do_action(t_all *all, int i)
{
	t_philo	philo;

	philo = all->philos[i];
	pthread_mutex_lock(&(all->forks[philo.fork_left]));
	print_action("\033[1;33m has taken a left fork \033[0;37m", all,
		philo.num, philo.fork_left);
	pthread_mutex_lock(&(all->forks[philo.fork_right]));
	print_action("\033[1;33m has taken a right fork \033[0;37m", all,
		philo.num, philo.fork_right);
	print_action("\033[1;32m is eating \033[1;37m", all, philo.num, -1);
	all->n_eat++;
	all->philos[i].t_die = get_time();
	if (!wait_action(all, all->time_eat) && (all->n_eat < all->qtt_eat
			|| all->qtt_eat == -1) && all->dead == 0 )
	{
		print_action("\033[1;34m is Sleeping\033[1;37m", all, philo.num, -1);
		pthread_mutex_unlock(&(all->forks[philo.fork_left]));
		pthread_mutex_unlock(&(all->forks[philo.fork_right]));
		if (!wait_action(all, all->time_sleep) && all->n_eat < all->qtt_eat
			&& all->dead == 0)
			print_action("\033[1;36m is Thinking\033[1;37m", all, philo.num, -1);
	}
}

int	wait_action(t_all *all, long long time)
{
	long long	i;

	i = get_time();
	while (!(all->dead))
	{
		if (diff_time(i) >= time)
			return (0);
		usleep(50);
	}
	return (1);
}
