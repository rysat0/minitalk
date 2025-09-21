/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rysato <rysato@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 15:19:16 by rysato            #+#    #+#             */
/*   Updated: 2025/09/21 20:05:26 by rysato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_state		g_state = {0, 0, 0};

static void	sig_handler(int sig, siginfo_t *info, void *ucontext)
{
	int	bit;

	bit = 0;
	(void)ucontext;
	g_state.sender = info->si_pid;
	if (sig == SIGUSR1)
		bit = 0;
	else if (sig == SIGUSR2)
		bit = 1;
	g_state.buf = (g_state.buf << 1) | bit;
	g_state.bits++;
	if (g_state.bits == 8)
	{
		if (g_state.buf == 0)
		{
			write(1, "\n", 1);
			kill(g_state.sender, SIGUSR2);
		}
		else
			write(1, &g_state.buf, 1);
		g_state.buf = 0;
		g_state.bits = 0;
	}
	kill(g_state.sender, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = sig_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		return (1);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		return (1);
	ft_printf("Server PID: %d\n", (int)getpid());
	while (1)
		pause();
	return (0);
}
