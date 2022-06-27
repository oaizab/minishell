/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 07:24:40 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/27 09:14:29 by oaizab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_psignal(int sig)
{
	if (sig == SIGINT)
		ft_putstr("\n");
	if (sig == SIGQUIT)
		ft_putstr("Quit: 3\n");
}

void	ft_wait(void)
{
	int		status;

	while (wait(&status) != -1)
	{
		if (WIFEXITED(status))
		{
			g_exit_status = WEXITSTATUS(status);
		}
		else if (WIFSIGNALED(status))
		{
			ft_psignal(WTERMSIG(status));
			g_exit_status = 128 + WTERMSIG(status);
		}
	}
}
