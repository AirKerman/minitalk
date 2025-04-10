/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerman <rkerman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:07:32 by rkerman           #+#    #+#             */
/*   Updated: 2025/04/10 15:02:40 by rkerman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_bit;

static int	len_receiver(siginfo_t *info, int *len, int reset)
{
	static int	i;

	if (!reset && i < 32)
	{
		if (info->si_signo == 10)
			*len = (*len | (1 << (31 - i)));
		kill(info->si_pid, SIGUSR1);
		i++;
		return (1);
	}
	else if (reset)
	{
		i = 0;
		len = 0;
	}
	return (0);
}

static void	character_treatment(char c, char **s, siginfo_t *info, int *len)
{
	static int	j;

	if (c != '\0')
	{
		(*s)[j] = (char)c;
		j++;
	}
	else
	{
		(*s)[j] = (char)c;
		write(1, "[", 1);
		ft_putpid(info->si_pid);
		write(1, "] ", 2);
		write(1, *s, ft_strlen(*s));
		write(1, "\n", 1);
		len_receiver(info, len, 1);
		j = 0;
		free(*s);
		*s = NULL;
	}
}

static void	signal_treatment(int signum, char *c)
{
	if (signum == 10)
		*c = (*c & ~(1 << (g_bit - 1))) + (1 << (g_bit - 1));
	if (signum == 12)
		*c = (*c & ~(1 << (g_bit - 1)));
}

static void	signal_handler(int signum, siginfo_t *info, void *ucontext)
{
	static char	c;
	static char	*s;
	static int	len;

	(void)ucontext;
	if (!len_receiver(info, &len, 0))
	{
		if (!s)
		{
			s = malloc(len + 1 * sizeof(char));
			if (!s)
			{
				kill(info->si_pid, SIGUSR2);
				exit(0);
			}
		}
		if (!g_bit)
			g_bit = 8;
		signal_treatment(signum, &c);
		g_bit--;
		if (!g_bit)
			character_treatment(c, &s, info, &len);
		kill(info->si_pid, SIGUSR1);
	}
}

int	main(void)
{
	struct sigaction	sig;

	sig.sa_sigaction = signal_handler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = SA_RESTART | SA_SIGINFO;
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	banner();
	write(1, "               ", 15);
	write(1, "                                             |", 46);
	write(1, "PID : ", 6);
	ft_putpid(getpid());
	write(1, "|              ", 15);
	write(1, "                                              \n", 47);
	while (1)
		pause();
	return (1);
}
