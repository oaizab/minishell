/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 14:33:40 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/26 07:14:56 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Count the number of strings in NULL terminated string array.
 *
 * @param args: NULL terminated string array
 * @return int: Number of strings
 */
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

/**
 * @brief Output arguments separated by space, terminated with a newline. In -n
 * is specified the trailing newline is suppressed.
 *
 * @param args: Argument string array
 * @param fd: File descriptor to output to
 * @return int: ft_echo always returns 0
 */
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
