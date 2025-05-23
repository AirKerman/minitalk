/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:45:52 by rkerman           #+#    #+#             */
/*   Updated: 2025/04/10 14:49:05 by rkerman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
