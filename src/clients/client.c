/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:08:32 by rkerman           #+#    #+#             */
/*   Updated: 2025/04/02 15:23:31 by rkerman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
# include <signal.h>
# include <stdlib.h>
# include <stdio.h>
# include <time.h>
# include <unistd.h>

int		ft_atoi(char *str)
{
	int	count;
	int	neg;

	neg = 1;
	count = 0;
	if (!str)
		return (count);
	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			neg = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		count = (count * 10) + (*str - 48);
		str++;
	}
	return (count * neg);
}

void	sending_str(int pid, char *str)
{
	int	itr;

	while (*str)
	{
		itr = 7;
		while (itr >= 0)
		{
			if (*str & (1 << itr))
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			itr--;
			usleep(100);
		}
		str++;
	}
	
}

int main(int argc, char **argv)
{
	int	pid;

	if (argc - 1 == 2 && (pid = ft_atoi(argv[1])))
	{
		sending_str(pid, argv[2]);
	}

}
