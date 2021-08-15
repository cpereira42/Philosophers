/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 17:33:52 by cpereira          #+#    #+#             */
/*   Updated: 2021/08/14 12:36:24 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// status

/*
	philo comeca no status 0 e vai comer, qundo terminar de comer, reseta o time_sleep e time_die, a altera ststus para 1
	quando terminar de dormir, altera o status para 0 que é pensando, e por ai vai.

*/
#include "philo.h"

void *timming (void* arg)
{
	int i;
	//long long tim;
	t_all *all;
	all = (t_all *)arg;

//	printf("ooo\n");
	////usleep(10);
//	printf("%d\n",diff_time(all->philos[0].t_die));
//	printf("ooo\n");

	while (1)
	{
		i = 0;
		while (i < all->qtt_philo)
		{
			if (diff_time(all->philos[i].t_eat) >= all->time_eat && all->philos[i].status == 1 ) // terminou de comer
			{
				//tim = ;
				all->philos[i].t_die = get_time();
				all->philos[i].t_sleep = get_time();
				all->philos[i].status = 2;
			}

			if (diff_time(all->philos[i].t_die) >= all->time_die)
			{
				printf("morre inferno fdp\n")	;
				printf ("status 1 = %d %d\n",all->philos[0].status, diff_time(all->philos[0].t_die));
				printf ("status 2 = %d %d\n",all->philos[1].status, diff_time(all->philos[1].t_die));
				printf ("status 3 = %d %d\n",all->philos[2].status, diff_time(all->philos[2].t_die));
				printf ("status 4 = %d %d\n",all->philos[3].status, diff_time(all->philos[3].t_die));
				exit(0);
			}

			if (diff_time(all->philos[i].t_sleep) >= all->time_sleep && all->philos[i].status == 3)
			{
				all->philos[i].status = 0; // vai pensar
			}


			//if (all->philos[i].status == 1)
			/*if (diff_time(all->philos[i].t_die) > all->time_die)
			{
				printf ("status = %d %d\n",all->philos[i].status, diff_time(all->philos[i].t_die));
				all->philos[i].status = -1; // morreu
				print_action("\033[1;31m died \033[1;37m", all,all->philos[i].num, -1);
				//printf("%d Philo %d died\n", diff_time(all->init_time) ,i + 1);
				exit (0);
			}*/
			i++;
			//usleep(1);
		}
	}
	printf("aaa\n");
}

void print_action(char *action, t_all *all, int i, int num)
{
	pthread_mutex_unlock(&(all->write));
	if (num >= 0)
		printf("%d Philo %d %s %d\n",diff_time(all->init_time), i, action, num);
	else
		printf("%d Philo %d %s\n",diff_time(all->init_time), i, action);
	pthread_mutex_lock(&(all->write));
}

void *action (void* arg)
{
	int i;
	//long long tim;
	t_all *all;
	t_philo philo;
	all = (t_all *)arg;

	i = all->curr;
	philo = all->philos[i];
	//long long tim;

	/*philo.t_die = all->time_die;
	philo.t_sleep = all->time_sleep;
	philo.t_eat = all->time_eat;*/

	////usleep(100);
	//if (philo.num == 1)
	//printf("sleep *$= %lldd die %lld status = %d\n",philo.t_sleep,philo.t_die,philo.num);
	all->philos[i].status = 0;
	all->init_time = get_time();
	while (all->philos[i].status != 4) // terminou de jantar
	{
		if (all->philos[i].status == 0) // vai comer
		{
			//print_action("is thinking", all,philo.num, -1);
			pthread_mutex_lock(&(all->forks[philo.fork_left]));
			print_action("\033[1;33m has taken a left fork \033[0;37m", all,philo.num, philo.fork_left);
			pthread_mutex_lock(&(all->forks[philo.fork_right]));
			print_action("\033[1;33m has taken a right fork \033[0;37m", all,philo.num, philo.fork_right);
			print_action("\033[1;32m is eating \033[1;37m", all,philo.num, -1);
			/*printf ("philo %d , statuss = %d t_die = %lld \n",all->philos[0].num,all->philos[0].status,all->philos[0].t_die);
			printf ("philo %d , statuss = %d t_die = %lld \n",all->philos[1].num,all->philos[1].status,all->philos[1].t_die);
			printf ("philo %d , statuss = %d t_die = %lld \n",all->philos[2].num,all->philos[2].status,all->philos[2].t_die);
			printf ("philo %d , statuss = %d t_die = %lld \n",all->philos[3].num,all->philos[3].status,all->philos[3].t_die);*/
			//; //  inicia horario de morte
			all->philos[i].t_die = get_time();
			all->philos[i].t_eat = get_time(); //  inicia horario de comida

			//usleep(10);
			/*printf("kkk\n");
			printf ("philo %d , statuss = %d t_die = %lld \n",all->philos[0].num,all->philos[0].status,all->philos[0].t_die);
			printf ("philo %d , statuss = %d t_die = %lld \n",all->philos[1].num,all->philos[1].status,all->philos[1].t_die);
			printf ("philo %d , statuss = %d t_die = %lld \n",all->philos[2].num,all->philos[2].status,all->philos[2].t_die);
			printf ("philo %d , statuss = %d t_die = %lld \n",all->philos[3].num,all->philos[3].status,all->philos[3].t_die);*/
			all->philos[i].status = 1; // status = comendo
			//all->philos[i].t_die = get_time();
		}
		if (all->philos[i].status == 2) // vai dormir
		{
			print_action("\033[1;34m is sleeping\033[1;37m", all,philo.num, -1);
			pthread_mutex_unlock(&(all->forks[philo.fork_left]));
			pthread_mutex_unlock(&(all->forks[philo.fork_right]));
			all->philos[i].status = 3;
		}
	}
	print_action("*Fim*", all,philo.num, -1);

	printf("fim\n");
	return NULL;
}
