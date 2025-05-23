/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerman <rkerman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 21:22:39 by rkerman           #+#    #+#             */
/*   Updated: 2025/04/10 14:58:44 by rkerman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

/*
	Shared Utils
*/

int		ft_strlen(char *str);

/*
	Server Utils
*/

void	banner(void);
void	ft_putpid(pid_t n);
