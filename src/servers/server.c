/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerman <rkerman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:07:32 by rkerman           #+#    #+#             */
/*   Updated: 2025/04/07 14:34:12 by rkerman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	bit;

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

/*int	ft_atoi(char *str)
{

}
*/
#include <stdio.h>
/*
char	*ft_strjoin(unsigned char *s, unsigned char c)
{
	unsigned char *str;

	str 
}
*/
void signal_handler(int signum, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	static long long c;
//	unsigned char cha;
//	static unsigned char *s;

	if (!bit)
		bit = 64;
	if (signum == 10)
		c = (c & ~(1 << (bit - 1))) + (1 << (bit - 1));
	if (signum == 12)
		c = (c & ~(1 << (bit - 1))) + (0 << (bit - 1));
	bit--;
	if (!bit)
	{
//		s = ft_strjoin(s, c);
		printf("%lld\n", c);
		write(1, &c, 1);
	}
	kill(info->si_pid, SIGUSR1);
}
int	main(void)
{
	struct sigaction	sig;

	sig.sa_sigaction = signal_handler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = SA_SIGINFO;
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
