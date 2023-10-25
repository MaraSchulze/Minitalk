/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 11:35:03 by marschul          #+#    #+#             */
/*   Updated: 2023/10/25 20:26:57 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_data[3];

void	handler1(int signal, siginfo_t *info, void *ucontext)
{
	unsigned char	byte;

	byte = (unsigned char) g_data[0];
	g_data[2] = info->si_pid;
	byte = byte << 1;
	byte = byte + 0;
	g_data[0] = (int) byte;
	g_data[1] = 1;
	signal++;
	ucontext++;
}

void	handler2(int signal, siginfo_t *info, void *ucontext)
{
	unsigned char	byte;

	byte = (unsigned char) g_data[0];
	g_data[2] = info->si_pid;
	byte = byte << 1;
	byte = byte + 1;
	g_data[0] = (int) byte;
	g_data[1] = 1;
	signal++;
	ucontext++;
}

void	fill_sigaction(int signal_, void (*handler) \
	(int signal, siginfo_t *info, void *ucontext))
{
	sigset_t			mask;
	struct sigaction	act;
	struct sigaction	oldact;

	if (sigemptyset(&mask) == -1)
		exit(-1);
	if (sigaddset(&mask, signal_) == -1)
		exit(-1);
	act.sa_sigaction = handler;
	act.sa_flags = SA_SIGINFO | SA_RESTART;
	if (sigaction(signal_, &act, &oldact) == -1)
		exit(-1);
}

int	main(int argc, char **argv)
{
	int		bitcounter;
	char	*pid;

	argc++;
	argv++;
	pid = ft_itoa(getpid());
	fill_sigaction(SIGUSR1, handler1);
	fill_sigaction(SIGUSR2, handler2);
	write(1, pid, ft_strlen(pid));
	free(pid);
	bitcounter = 0;
	while (1)
	{
		while (g_data[1] == 0)
			usleep(1);
		if (bitcounter == 7)
		{
			write(1, &(g_data[0]), 1);
			bitcounter = 0;
		}
		else
			bitcounter++;
		g_data[1] = 0;
		kill(g_data[2], SIGUSR1);
	}
}
