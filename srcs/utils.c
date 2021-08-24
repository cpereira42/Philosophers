/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 19:33:50 by cpereira          #+#    #+#             */
/*   Updated: 2021/08/23 10:49:05 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

static size_t	ft_strlen(const char *frase)
{
	int	i;

	i = 0;
	while (frase[i] != '\0')
		i++;
	return (i);
}

long	ft_atoi(const char *str)
{
	const char		*frase;
	long			total;
	unsigned int	i;
	int				mult;

	frase = (const char *)str;
	i = 0;
	total = 0;
	mult = 1;
	if (ft_strlen(frase) == 0)
		return (0);
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == ' ')
		i++;
	if (frase[i] == '-')
		mult = -1;
	if (frase[i] == '-' || frase[i] == '+')
		i++;
	while (ft_isdigit(frase[i]))
	{
		total = total * 10 + frase[i] - 48;
		i++;
	}
	return (total * mult);
}

int	verify_args(t_all *all, int j)
{
	long	num;
	int		i;

	if (all->argc > 6 || all->argc <= 4)
	{
		printf("Wrong Args\n");
		return (1);
	}
	i = 1;
	while (j < (int)ft_strlen(all->argv[i]))
	{
		if (!ft_isdigit(all->argv[i][j]) && all->argv[i][0] != '-')
			return (1);
		if (all->argv[i][1] == '-')
			return (1);
		j++;
	}
	if (all->argv[i][0] == '-')
		num = ft_atoi(&all->argv[i][1]) * -1;
	else
		num = ft_atoi(&all->argv[i][0]);
	if (num > 2147483647 || num < -2147483648 )
		return (1);
	return (0);
}

void	drop_forks(t_all *all)
{
	int	i;

	i = 0;
	while (i <= all->qtt_philo)
	{
		pthread_mutex_unlock(&(all->forks[i]));
		i++;
	}
}
