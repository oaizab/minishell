/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 14:33:40 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/30 18:21:01 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check if string is a valid echo flag. Valid flag comply to the
 * following regex: ^-(n)*$
 *
 * @param str: string to check
 * @return bool: true if string is a valid flag, false otherwise
 */
static bool	ft_is_valid_option(char *str)
{
	int	i;

	if (str[0] != '-')
	{
		return (false);
	}
	i = 1;
	while (str[i] != '\0' && str[i] == 'n')
	{
		++i;
	}
	if (str[i] == '\0')
	{
		return (true);
	}
	else
	{
		return (false);
	}
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
	while (args[i] != NULL)
	{
		if (ft_is_valid_option(args[i]) == true)
			end = '\0';
		else
		{
			ft_putstr_fd(args[i], fd);
			if (i != argc - 1)
				ft_putchar_fd(' ', fd);
		}
		i++;
	}
	ft_putchar_fd(end, fd);
	return (0);
}
