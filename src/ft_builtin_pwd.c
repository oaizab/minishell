/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 09:24:38 by hhamza            #+#    #+#             */
/*   Updated: 2022/06/30 10:07:49 by oaizab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Print current working directory.
 *
 * @return int: 0 if success, 1 on failure
 */
int	ft_pwd(int fd, t_env *env)
{
	char	*cwd;

	cwd = ft_env_get(env, "PWD", false);
	if (cwd == NULL)
	{
		cwd = "";
	}
	ft_fprintf(fd, "%s\n", cwd);
	return (0);
}
