/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 00:08:11 by cpereira          #+#    #+#             */
/*   Updated: 2021/08/14 11:30:47 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_all	all;

	all.argv = argv;
	all.argc = argc;
	if (verify_args(&all, 0))
	{
		printf("Wrong entry\n");
		return (1);
	}

	/*long long t1;
	long long t2;

	t1 = get_time();
	usleep(200000);
	t2 = get_time();
	printf ("t1 = %lld t2 = %lld , dif = %d\n", t1, t2, diff_time(t1));
	exit (0);*/
	get_info(&all, 0, 0, 0);
	if (create_philos(&all, 0))
		exit (1);
	create_thread(&all);
	return (0);
}

void	create_thread(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->qtt_philo)
	{
		all->curr = i;
		pthread_create(&all->philos[i].id, NULL, action, (void *) all);
		usleep(50);
		i++;
	}
	i = 0;
	pthread_create(&all->tim, NULL, timming, (void *) all);
	//pthread_join(all->tim, NULL);
	while (i < all->qtt_philo)
	{
		pthread_join(all->philos[i].id, NULL);
		i++;
	}
}

int	create_philos(t_all *all, int i)
{
	int	next;

	all->philos = (t_philo *)malloc(sizeof(t_philo) * (all->qtt_philo + 1));
	if (all->philos == NULL)
		return (1);
	all->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* (all->qtt_philo + 1));
	if (all->forks == NULL)
		return (1);
	while (i < all->qtt_philo)
	{
		if (i == all->qtt_philo - 1)
			next = 0;
		else
			next = i + 1;
		if (pthread_mutex_init(&(all->forks[i]), NULL))
			return (1);
		all->philos[i].num = i + 1;
		all->philos[i].fork_left = i;
		all->philos[i].fork_right = next;
		long long tim;
		tim = get_time();
		all->philos[i].t_die = tim;
		all->philos[i].t_eat = tim;
		all->philos[i].t_sleep = tim;
		all->curr = i;
		i++;
	}
	return (0);
}

void	get_info(t_all *all, int t_die, int t_eat, int t_sleep)
{
	all->time_die = (int)ft_atoi(all->argv[2]);
	all->time_eat = (int)ft_atoi(all->argv[3]);
	all->time_sleep = (int)ft_atoi(all->argv[4]);
	all->curr = 0;
	all->qtt_philo = (int)ft_atoi(all->argv[1]);
	if (all->argc == 4)
		all->qtt_eat = ft_atoi(all->argv[5]);
	else
		all->qtt_eat = -1;
	if (all->qtt_philo < 0 || t_die < 0 || t_eat < 0 || t_sleep < 0)
	{
		printf("Args can't be negative");
		exit(1);
	}
}
