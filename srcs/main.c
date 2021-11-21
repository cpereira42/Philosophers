/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 00:08:11 by cpereira          #+#    #+#             */
/*   Updated: 2021/08/23 11:38:29 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_all	all;

	all.argv = argv;
	all.argc = argc;
	all.n_eat = 0;
	if (verify_args(&all, 0))
	{
		printf("Wrong entry\n");
		return (1);
	}
	if (get_info(&all))
		return (1);
	if (create_philos(&all, 0, 0))
		return (1);
	create_thread(&all);
	pthread_mutex_unlock(&(all.write));
	end_threads(&all);
	free (all.philos);
	free (all.forks);
	return (0);
}

void	end_threads(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->qtt_philo)
	{
		pthread_mutex_destroy(&(all->forks[i]));
		i++;
	}
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
	pthread_join(all->tim, NULL);
	while (i < all->qtt_philo && all->qtt_philo > 1)
	{
		pthread_join(all->philos[i].id, NULL);
		i++;
	}
}

int	create_philos(t_all *all, int i, int next)
{
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
		all->philos[i].t_die = get_time();
		all->philos[i].t_eat = get_time();
		all->philos[i].t_sleep = get_time();
		all->curr = i;
		i++;
	}
	return (0);
}

int	get_info(t_all *all)
{
	all->time_die = (int)ft_atoi(all->argv[2]);
	all->time_eat = (int)ft_atoi(all->argv[3]);
	all->time_sleep = (int)ft_atoi(all->argv[4]);
	all->curr = 0;
	all->qtt_philo = (int)ft_atoi(all->argv[1]);
	if (all->argc == 6)
		all->qtt_eat = ft_atoi(all->argv[5]) * all->qtt_philo;
	else
		all->qtt_eat = -1;
	if (all->time_die < 60 || all->time_eat < 60 || all->time_sleep < 60)
	{
		printf("Times can't be less 60 ms\n");
		return (1);
	}
	if (all->qtt_philo > 200 || all->qtt_philo < 0)
	{
		printf("Numbers of Philos can't be more then 200 ou Less 0\n");
		return (1);
	}
	return (0);
}
