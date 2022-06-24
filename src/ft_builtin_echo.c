/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 14:33:40 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/19 16:21:36 by oaizab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **args, int fd)
{
	char	end;
	int		i;

	i = 1;
	end = '\n';
	if (ft_strcmp(args[1], "-n") == 0)
		end = '\0';
	while (args[i])
	{
		ft_putstr_fd(args[i], fd);
		i++;
	}
	ft_putchar_fd(end, fd);
	return (0);
}
