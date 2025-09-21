/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rysato <rysato@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 15:19:18 by rysato            #+#    #+#             */
/*   Updated: 2025/09/21 20:18:08 by rysato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// volatile: 最適化せず毎回RAMから取得
// sig_atomic_t: atomicな変数で、シグナルにより処理が中断されない
volatile sig_atomic_t	g_flag = 0;

static void	ack_handler(int sig)
{
	if (sig == SIGUSR1)
		g_flag |= ACK_BIT;
	if (sig == SIGUSR2)
		g_flag |= FIN_BIT;
}

static void	send_char(pid_t ser_pid, unsigned char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		g_flag &= ~ACK_BIT;
		if (((c >> i) & 1) == 1)
			kill(ser_pid, SIGUSR2);
		else
			kill(ser_pid, SIGUSR1);
		while (!(g_flag & ACK_BIT))
			pause();
		i--;
	}
}

int	main(int argc, char **argv)
{
	pid_t				ser_pid;
	char				*msg;
	struct sigaction	sa;
	size_t				len;

	len = 0;
	if (argc != 3)
		return (write(1, "Usage: ./client <server pid> <message>\n", 40), 1);
	ser_pid = ft_atoi(argv[1]);
	msg = argv[2];
	sa.sa_handler = ack_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (len < ft_strlen(msg))
	{
		send_char(ser_pid, (unsigned char)msg[len]);
		len++;
	}
	send_char(ser_pid, 0);
	while (!(g_flag & FIN_BIT))
		pause();
	return (0);
}
