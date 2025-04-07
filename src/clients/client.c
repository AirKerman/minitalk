/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:08:32 by rkerman           #+#    #+#             */
/*   Updated: 2025/04/07 14:33:37 by rkerman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>


int	g_pause;

long long	ft_atoi(char *str)
{
	long long	count;
	long long	neg;

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

void	signal_handler(int signum, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	(void)info;
	if (signum == 10)
		g_pause = 0;
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	sender_str(int pid, char *str)
{
	int	itr;

	while (*str)
	{
		itr = 7;
		while (itr >= 0)
		{
			while (g_pause)
				usleep(0);
			g_pause = 1;
			if (*str & (1 << itr))
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			itr--;
		}
		str++;
	}
}

void	sender_len(int p, long long l)
{
	long long	itr;

	itr = 63;
	while (itr >= 0)
	{
		while (g_pause)
			usleep(0);
		g_pause = 1;
		if (l & (1 << itr))
			kill(p, SIGUSR1);
		else
			kill(p, SIGUSR2);
		itr--;
	}
}


int	main(int argc, char **argv)
{
	struct sigaction	sig;
	int					pid;

	sig.sa_sigaction = signal_handler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sig, NULL);
	pid = ft_atoi(argv[1]);
	if (argc - 1 == 2 && pid)
		sender_len(pid, ft_atoi(argv[2]));
		//sender_str(pid, argv[2]);
}
