/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 09:24:38 by hhamza            #+#    #+#             */
/*   Updated: 2022/06/27 08:47:28 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		perror("minishell: pwd");
		return (1);
	}
	ft_fprintf(fd, "%s\n", cwd);
	free(cwd);
	return (0);
}
