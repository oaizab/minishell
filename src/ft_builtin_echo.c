/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 14:33:40 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/25 17:48:47 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
	{
		i++;
	}
	return (i);
}

int	ft_echo(char **args, int fd)
{
	int		argc;
	char	end;
	int		i;

	argc = ft_count_args(args);
	if (argc == 1)
	{
		return (ft_putchar_fd('\n', fd), 0);
	}
	end = '\n';
	i = 1;
	if (ft_strcmp(args[1], "-n") == 0)
	{
		end = '\0';
		++i;
	}
	while (args[i] != NULL)
	{
		ft_putstr_fd(args[i], fd);
		if (i != argc - 1)
			ft_putchar_fd(' ', fd);
		i++;
	}
	ft_putchar_fd(end, fd);
	return (0);
}
