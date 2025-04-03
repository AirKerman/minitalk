/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:08:32 by rkerman           #+#    #+#             */
/*   Updated: 2025/04/03 23:06:24 by rkerman          ###   ########.fr       */
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

void signal_handler(int signum, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	(void)info;
	(void)signum;
}

void	sending_str(int pid, char *str)
{
	int	itr;

	while (*str)
	{
		itr = 7;
		while (1)
		{
			usleep(100);
			if (*str & (1 << itr))
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			itr--;
			if (!(itr >= 0))
				break ;
		}
		str++;
	}
	
}

int main(int argc, char **argv)
{
	int	pid;
	struct sigaction        sig;

	sig.sa_sigaction = signal_handler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sig, NULL);
	if (argc - 1 == 2 && (pid = ft_atoi(argv[1])))
	{
		sending_str(pid, argv[2]);
	}

}
