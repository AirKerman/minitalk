/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerman <rkerman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:07:32 by rkerman           #+#    #+#             */
/*   Updated: 2025/04/10 00:51:29 by rkerman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_bit;

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	banner(void)
{
	char	*banner;

	banner = " \n\033[32m\
    /$$          /$$ /$$          /$$      /$$ /$$           /$$   /$$               /$$ /$$   /$$          /$$ /$$          /$$     \n\
   /$$/         /$$/|  $$        | $$$    /$$$|__/          |__/  | $$              | $$| $$  /$$/         /$$/|  $$        |  $$   \n\
  /$$/         /$$/  \\  $$       | $$$$  /$$$$ /$$ /$$$$$$$  /$$ /$$$$$$    /$$$$$$ | $$| $$ /$$/         /$$/  \\  $$        \\  $$  \n\
 /$$/         /$$/    \\  $$      | $$ $$/$$ $$| $$| $$__  $$| $$|_  $$_/   |____  $$| $$| $$$$$/         /$$/    \\  $$        \\  $$ \n\
|  $$        |  $$     /$$/      | $$  $$$| $$| $$| $$  \\ $$| $$  | $$      /$$$$$$$| $$| $$  $$        |  $$     /$$/         /$$/ \n\
 \\  $$        \\  $$   /$$/       | $$\\  $ | $$| $$| $$  | $$| $$  | $$ /$$ /$$__  $$| $$| $$\\  $$        \\  $$   /$$/         /$$/  \n\
  \\  $$        \\  $$ /$$/        | $$ \\/  | $$| $$| $$  | $$| $$  |  $$$$/|  $$$$$$$| $$| $$ \\  $$        \\  $$ /$$/         /$$/   \n\
   \\__/         \\__/|__/         |__/     |__/|__/|__/  |__/|__/   \\___/   \\_______/|__/|__/  \\__/         \\__/|__/         |__/    \n\
                                                                                                                                    \n\
                                                                                                                                    \n\
\033[0m\n";
	write(1, banner, ft_strlen(banner));
}

void	ft_putpid(pid_t n)
{
	if (n > 9)
	{
		ft_putpid(n / 10);	
		ft_putpid(n % 10);
	}
	else
	{
		n += 48;
		write(1, &n, 1);
	}
}

int	len_receiver(siginfo_t *info, int *len, int reset)
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

void	character_treatment()
{

}

void signal_handler(int signum, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	static char c;
	static char *s;
	static int		len;
	static int		j;

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
		if (signum == 10)
			c = (c & ~(1 << (g_bit - 1))) + (1 << (g_bit - 1));
		if (signum == 12)
			c = (c & ~(1 << (g_bit - 1)));
		g_bit--;
		if (!g_bit)
		{
			if (c != '\0')
			{
				s[j] = (char)c;
				j++;
			}
			else
			{
				s[j] = (char)c;
				write(1, "[", 1);
				ft_putpid(info->si_pid);
				write(1, "] ", 2);
				write(1, s, ft_strlen(s));
				write(1, "\n", 1);
				len_receiver(info, &len, 1);
				j = 0;
				free(s);
				s = NULL;
			}
		}
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
	write(1, "                                                            |", 61);
	write(1, "PID : ", 6);
	ft_putpid(getpid());
	write(1, "|                                                            \n", 62);
	
	while (1)
		pause();
	return (1);
}
