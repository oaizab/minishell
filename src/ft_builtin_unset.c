/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 16:30:27 by hhamza            #+#    #+#             */
/*   Updated: 2022/06/30 10:08:17 by oaizab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

/**
 * @brief Unset an environment variable.
 *
 * @param args: Arguments array
 * @param ft_env: Environment object
 * @return int: 0 on success, 1 on failure
 */
void	ft_unset(char **args, t_ft_env *ft_env)
{
	int	argc;
	int	i;

	argc = ft_count_args(args);
	if (argc == 1)
	{
		g_exit_status = 0;
	}
	i = 1;
	while (args[i] != NULL)
	{
		if (ft_validate_identifier(args[i]) == false)
		{
			ft_fprintf(STDERR_FILENO, \
				"minishell: unset: '%s': not a valid identifier\n", args[i]);
			g_exit_status = 1;
		}
		else
			(ft_remove_env(&ft_env->env, args[i]),
				ft_remove_env(&ft_env->export, args[i]));
		if (ft_strcmp(args[i], "PATH") == 0)
			ft_env_get(ft_env->env, "PATH", true);
		++i;
	}
	g_exit_status = 0;
}
