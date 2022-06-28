/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 09:20:05 by hhamza            #+#    #+#             */
/*   Updated: 2022/06/28 09:32:15 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char **args, t_ft_env *ft_env)
{
	int	argc;

	argc = ft_count_args(args);
	if (argc == 1)
	{
		return (0);
	}
	if (ft_validate_identifier(args[1]) == false)
	{
		ft_fprintf(STDERR_FILENO, \
			"minishell: unset: '%s': not a valid identifier\n", args[1]);
		return (1);
	}
	else
	{
		ft_remove_env(&ft_env->env, args[1]);
		ft_remove_env(&ft_env->export, args[1]);
		return (0);
	}
}
