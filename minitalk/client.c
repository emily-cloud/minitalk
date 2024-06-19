/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahua <huahua@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:32:27 by huahua            #+#    #+#             */
/*   Updated: 2024/04/20 22:17:23 by huahua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	ft_atoi(const char *str)
{
	long 	number;
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	number = 0;
	while ((str[i] <= 13 && str[i] >= 9) || str[i] == 32)
		i++;
	if(str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		number *= 10;
		number += str[i] - '0';
		i++;
	}
	return (number * sign);
}

void message_sender(char c, int pid)
{
	int bit_index;

	bit_index = 0;
	while (bit_index < 8)
	{
		if (c & (1 << bit_index))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(1000);
		bit_index++;
	}
}

void sent_finished(int sagnum)
{
	if(sagnum == SIGUSR2)
		write(1, "message is sent succussfull\n", 28);
}

int main(int argc, char **argv)
{
	int pid;
	int i;
	struct sigaction sa_message;

	if(argc == 3)
	{
		sa_message.sa_handler= sent_finished;
		if(sigaction(SIGUSR1, &sa_message, NULL) == -1)
			return (4);
		if(sigaction(SIGUSR2, &sa_message, NULL) == -1)
			return (5);
		pid = ft_atoi(argv[1]);
		i = 0;
		while(argv[2][i])
		{
			message_sender(argv[2][i], pid);
			i++;
		}
		message_sender('\n',pid);
	return (0);
	}
	else
		write(1,"input Error\n", 12);
	return (4);
}
