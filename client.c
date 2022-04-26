/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/15 10:51:55 by dsaat         #+#    #+#                 */
/*   Updated: 2022/04/26 18:46:15 by dsaat         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <signal.h>

static void	error_check(int code)
{
	if (code == -1)
		exit(EXIT_FAILURE);
}

static void	send_char_bit(int pid, char *str)
{
	static char	*g_message;
	static int	bitindex = 0;
	int			bit;

	if (str)
		g_message = str;
	if (!*g_message)
	{
		ft_putstr_fd("message received!\n", 1);
		exit(EXIT_SUCCESS);
	}
	bit = *g_message >> bitindex & 1;
	bitindex = (bitindex + 1) % 8;
	if (bitindex == 0)
		g_message++;
	error_check(kill(pid, SIGUSR1 + bit));
}

static void	handle_sigusr(int sig, siginfo_t *info, void *ucontext)
{
	(void) sig;
	(void) ucontext;
	send_char_bit(info->si_pid, NULL);
}

int	main(int argc, char **argv)
{
	struct sigaction	act;

	if (argc != 3)
	{
		ft_putstr_fd("ERROR: input server PID followed by string!\n", 1);
		exit(EXIT_FAILURE);
	}
	sigemptyset(&act.sa_mask);
	act.sa_sigaction = handle_sigusr;
	act.sa_flags = SA_SIGINFO | SA_NODEFER;
	error_check(sigaction(SIGUSR1, &act, NULL));
	send_char_bit(atoi(argv[1]), argv[2]);
	while (1)
		pause();
}
