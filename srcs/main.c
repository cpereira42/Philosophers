/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 00:08:11 by cpereira          #+#    #+#             */
/*   Updated: 2021/07/27 20:02:48 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_all	all;

	if (argc > 6 || argc <= 4)
	{
		printf("Wrong Args\n");
		return (1);
	}
	all.argv = argv;
	all.argc = argc;
	if (verify_args(&all))
	{
		printf("Wrong entry\n");
		return (1);
	}
	get_info(&all);
	printf("Hello Philosophers\n");
	printf("qtt philosophers %d\n", all.qtt_philo);
	printf("time to die %d\n", all.t_die);
	printf("time to eat %d\n", all.t_eat);
	printf("time to sleep %d\n", all.t_eat);
	printf("How many time to eat %d\n", all.qtt_philo);
	return (0);
}

void	get_info(t_all *all)
{
	all->qtt_philo = (int)ft_atoi(all->argv[1]);
	all->t_die = (int)ft_atoi(all->argv[2]);
	all->t_eat = (int)ft_atoi(all->argv[3]);
	all->t_sleep = (int)ft_atoi(all->argv[4]);
	if (all->argc == 4)
		all->qtt_eat = ft_atoi(all->argv[5]);
	else
		all->qtt_eat = -1;
}
