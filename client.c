/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samberna <samberna@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 18:09:32 by samberna          #+#    #+#             */
/*   Updated: 2024/12/11 23:06:55 by samberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int RECV_RESP = 0;

int	ft_atoi(const char *str)
{
	int	n;

	n = 0;
	while (*str >= '0' && *str <= '9')
	{
		n = n * 10 + *str - '0';
		str++;
	}
	return (n);
}

void	send_char(int pid, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (c & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		c >>= 1;
		while (RECV_RESP == 0)
			usleep(50);
		RECV_RESP = 0;
		i++;
	}
}

void	send_str(int pid, char *str)
{
	while (*str)
	{
		send_char(pid, *str);
		str++;
	}
	send_char(pid, *str);
}

void handler(int n) {
	(void)n;
	RECV_RESP = 1;
}

int	main(int ac, char **av)
{
	int	pid;
	struct sigaction	sa;

	sa.sa_handler = handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	if (ac != 3)
	{
		write(1, "Usage: ./client [PID] [STRING]\n", 30);
		return (1);
	}
	pid = ft_atoi(av[1]);
	send_str(pid, av[2]);
	return (0);
}
