/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 09:24:38 by hhamza            #+#    #+#             */
/*   Updated: 2022/06/26 12:00:02 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int errno;

/**
 * @brief Print current working directory.
 *
 * @return int: 0 if success, 1 on failure
 */
int	ft_pwd(int fd)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		ft_fprintf(STDERR_FILENO, "minishell: pwd: %s\n", strerror(errno));
		return (1);
	}
	ft_fprintf(fd, "%s\n", cwd);
	free(cwd);
	return (0);
}
