/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahua <huahua@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 21:10:21 by huahua            #+#    #+#             */
/*   Updated: 2024/04/20 22:17:29 by huahua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n == -2147483648)
	{
		write(fd, "-", 1);
		write(fd, "2", 1);
		n = 147483648;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
	{
		c = n + '0';
		write(fd, &c, 1);
	}
}

void message_handle(int signum, siginfo_t *info, void *content)
{
	static int bit_index;
	static int i;

	(void)content;
	if(signum == SIGUSR1)
		i |= (1 << bit_index);
	bit_index++;
	if(bit_index == 8)
	{
		write(1, &i, 1);
		if(i == '\n')
		{
			if (kill(info->si_pid, SIGUSR2) == -1)
				return;
		}
		bit_index = 0;
		i = 0;
	}
}

int main(void)
{
	int pid;
	struct sigaction sa_message;

	pid = getpid();
	write(1, "My server PID: ", 15);
	ft_putnbr_fd(pid, 1);
	write(1, "\n", 1);
	while(1)
	{
		sa_message.sa_sigaction = message_handle;
		sa_message.sa_flags = SIGINFO;
		if (sigaction(SIGUSR1, &sa_message, NULL) == -1)
			return (1);
		if (sigaction(SIGUSR2, &sa_message, NULL) == -1)
			return (2);
		pause();
	}
}
