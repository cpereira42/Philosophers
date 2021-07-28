/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpereira <cpereira@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 01:19:17 by user42            #+#    #+#             */
/*   Updated: 2021/07/27 19:59:22 by cpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>

# define NUMX 10

typedef struct s_vect
{
	int				num;
	struct s_vect	*next;
}					t_vect;

typedef struct s_all
{
	int		argc;
	char	**argv;
	int		posic;
	int		qtt_philo;
	int		t_eat;
	int		t_sleep;
	int		t_die;
	int		qtt_eat;
}				t_all;

long	ft_atoi(const char *str);
int		verify_args(t_all *all);
void	get_info(t_all *all);

#endif
