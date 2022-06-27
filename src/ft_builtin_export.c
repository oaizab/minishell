/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 17:41:33 by hhamza            #+#    #+#             */
/*   Updated: 2022/06/27 20:54:27 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static void	ft_export_set(char *arg, t_ft_env *ft_env)
{
	char	*identifier;
	int		i;

	identifier = NULL;
	i = 0;
	while (arg[i] != '=' && arg[i] != '\0')
	{
		identifier = ft_append_char(identifier, arg[i]);
		++i;
	}
	if (arg[i] == '\0' && ft_env_find(ft_env->export, identifier) != NULL)
	{
		g_exit_status = 0;
		return ;
	}
	if (identifier == NULL || ft_validate_identifier(identifier) == false)
	{
		if (identifier == NULL)
			identifier = "=";
		ft_fprintf(STDERR_FILENO, \
			"minishell: export: '%s': not a valid identifier\n", identifier);
		g_exit_status = 1;
	}
	else
	{
		if (ft_strcmp(arg + i + 1, "") != 0)
			ft_env_add(&ft_env->env, identifier, arg + i + 1);
		ft_export_add(&ft_env->export, identifier, arg + i + 1);
		g_exit_status = 0;
	}
}

static void	ft_export_print(t_ft_env *ft_env)
{
	t_env	*iter;

	iter = ft_env->export;
	while (iter != NULL)
	{
		ft_printf("declare -x %s=\"%s\"\n", iter->key, iter->value);
		iter = iter->next;
	}
	g_exit_status = 0;
}

void	ft_export(char **args, t_ft_env *ft_env)
{
	int	argc;
	int	i;

	argc = ft_count_args(args);
	if (argc == 1)
	{
		ft_export_print(ft_env);
	}
	else
	{
		i = 1;
		while (args[i] != NULL)
		{
			ft_export_set(args[i], ft_env);
			++i;
		}
	}
}
