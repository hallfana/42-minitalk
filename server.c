/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samberna <samberna@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 18:14:07 by samberna          #+#    #+#             */
/*   Updated: 2024/12/11 23:47:42 by samberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const c)
{
	char	*res;
	size_t	i;

	if (!c)
		return (NULL);
	i = 0;
	res = (char *)malloc((ft_strlen(s1) + 2) * sizeof(char));
	if (!res)
		return (NULL);
	if (s1)
	{
		while (s1[i])
		{
			res[i] = s1[i];
			i++;
		}
	}
	res[i] = c;
	res[i + 1] = '\0';
	if (s1)
		free((char *)s1);
	return (res);
}

void	ft_putnbr(int n)
{
	char	c;

	if (n > 9)
		ft_putnbr(n / 10);
	c = n % 10 + '0';
	write(1, &c, 1);
}

#include <stdio.h>
void	handler(int signum, siginfo_t *info, void *ctx)
{
	static char	c = 0;
	static int	i = 0;
	static char	*str = NULL;
	//static int client_pid = 0;
	printf("sqd %d\n", info->si_pid);
	(void)ctx;
	//if (!client_pid)
	//	client_pid = info->si_pid;

	if (signum == SIGUSR1)
		c |= 1 << i;
	kill(info->si_pid, SIGUSR1);
	i++;
	if (i == 8)
	{
		if (c == '\0')
		{
			write(1, str, ft_strlen(str));
			write(1, "\n", 1);
			free(str);
			str = NULL;
		}
		else
			str = ft_strjoin(str, c);
		c = 0;
		i = 0;
	}
}

int	main(void)
{
	struct sigaction	s_sigaction;

	s_sigaction.sa_sigaction = handler;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_sigaction, NULL);
	sigaction(SIGUSR2, &s_sigaction, NULL);
	write(1, BANNER0, ft_strlen(BANNER0));
	write(1, BANNER1, ft_strlen(BANNER1));
	write(1, BANNER2, ft_strlen(BANNER2));
	write(1, BANNER3, ft_strlen(BANNER3));
	write(1, "Server PID: ", 12);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	while (1)
		pause();
	return (0);
}
