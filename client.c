/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 10:59:29 by marschul          #+#    #+#             */
/*   Updated: 2023/10/25 19:50:14 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_ack;

void	handler(int signal)
{
	g_ack = 1;
	signal++;
}

void	fill_handler(void)
{
	sigset_t			mask;
	struct sigaction	act;
	struct sigaction	oldact;

	if (sigemptyset(&mask) == -1)
		exit(-1);
	act.sa_handler = handler;
	if (sigaddset(&mask, SIGUSR1) == -1)
		exit(-1);
	act.sa_mask = mask;
	act.sa_flags = SA_RESTART;
	if (sigaction(SIGUSR1, &act, &oldact) == -1)
		exit(-1);
}

int	get_signal(char c, int bitcounter)
{
	unsigned char	mask;
	int				i;

	mask = (char) 128;
	i = 0;
	while (i < bitcounter)
	{
		mask = mask / 2;
		i++;
	}
	c = c & mask;
	if (c == 0)
		return (SIGUSR1);
	else
		return (SIGUSR2);
}

int	main(int argc, char **argv)
{
	char	*message;
	int		bitcounter;
	int		signal;

	if (argc != 3)
	{
		write(1, "Usage : client PID string", 25);
		return (-1);
	}
	message = argv[2];
	bitcounter = 0;
	fill_handler();
	while (*message != '\0')
	{
		signal = get_signal(*message, bitcounter % 8);
		bitcounter++;
		if (bitcounter % 8 == 0)
			message++;
		g_ack = 0;
		kill(ft_atoi(argv[1]), signal);
		while (g_ack == 0)
			usleep(1);
	}
	return (0);
}
