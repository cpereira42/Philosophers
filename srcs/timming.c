/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timming.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 17:32:11 by cpereira          #+#    #+#             */
/*   Updated: 2021/08/12 17:15:51 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	diff_time(long long last)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	if (last > 0)
		return ((t.tv_sec * 1000) + (t.tv_usec / 1000) - last);
	else
		return (0);
}

long long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}
