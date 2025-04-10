/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:08:32 by rkerman           #+#    #+#             */
/*   Updated: 2025/04/10 14:58:03 by rkerman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>

int	g_pause;

static long long	ft_atoi(char *str)
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

static void	signal_handler(int signum, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	if (signum == 10)
		g_pause = 0;
	if (signum == 12)
	{
		write(2, "Error server\n", 13);
		exit(0);
	}
}

static void	sender_char(int pid, int c, int itr)
{
	while (itr >= 0)
	{
		if (kill(pid, 0) == -1)
		{
			write(2, "Error pid\n", 10);
			exit(0);
		}
		while (g_pause)
			usleep(0);
		g_pause = 1;
		if (c & (1 << itr))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		itr--;
	}
}

static void	sender_str(int pid, char *str)
{
	int	len;

	len = ft_strlen(str);
	sender_char(pid, len, 31);
	while (*str)
	{
		sender_char(pid, *str, 7);
		str++;
	}
	sender_char(pid, '\0', 7);
	write(1, "Message sent successfuly\n", 25);
}

int	main(int argc, char **argv)
{
	struct sigaction	sig;
	int					pid;

	sig.sa_sigaction = signal_handler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	pid = ft_atoi(argv[1]);
	if (argc - 1 == 2 && pid)
		sender_str(pid, argv[2]);
}
