/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:08:32 by rkerman           #+#    #+#             */
/*   Updated: 2025/03/27 14:19:00 by rkerman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
# include <signal.h>
# include <stdlib.h>
# include <stdio.h>
# include <time.h>
int main(int argc, char **argv)
{
    union sigval sigval;
    pid_t pid;
    if (argc < 2 || (pid = atoi(argv[1])) < 0)
    return EXIT_FAILURE;
    sigval.sival_int = time(NULL);
    printf("sender: sending %d to PID %d\n",
        sigval.sival_int, pid);
    sigqueue(pid, SIGUSR1, sigval);
    return EXIT_SUCCESS;
}
