/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/15 10:51:53 by dsaat         #+#    #+#                 */
/*   Updated: 2022/04/26 18:50:07 by dsaat         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <signal.h>

static void	error_check(int code)
{
	if (code == -1)
		exit(EXIT_FAILURE);
}

static void	handle_sigusr(int sig, siginfo_t *info, void *ucontext)
{
	static char	c = 0;
	static int	bitindex = 0;

	(void) ucontext;
	if (sig == SIGUSR1)
		c = c | 1 << bitindex;
	bitindex = (bitindex + 1) % 8;
	if (bitindex == 0)
	{
		ft_putchar_fd(c, 1);
		c = 0;
	}
	error_check(kill(info->si_pid, SIGUSR1));
}

int	main(void)
{
	struct sigaction	act;

	sigemptyset(&act.sa_mask);
	act.sa_sigaction = handle_sigusr;
	act.sa_flags = SA_SIGINFO | SA_NODEFER;
	error_check(sigaction(SIGUSR1, &act, NULL));
	error_check(sigaction(SIGUSR2, &act, NULL));
	ft_putstr_fd("pid: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	while (1)
		pause();
}
