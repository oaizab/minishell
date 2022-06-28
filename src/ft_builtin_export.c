/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 17:41:33 by hhamza            #+#    #+#             */
/*   Updated: 2022/06/28 08:28:43 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static void	ft_export_error(char *arg)
{
	ft_fprintf(STDERR_FILENO, \
		"minishell: export: '%s': not a valid identifier\n", arg);
	g_exit_status = 1;
}

static void	ft_export_set(char *arg, t_ft_env *ft_env)
{
	char	*key;
	char	*value;
	char	*eq_ptr;

	eq_ptr = ft_strchr(arg, '=');
	if (eq_ptr == NULL)
	{
		if (ft_validate_identifier(arg) == true)
			ft_export_add(&ft_env->export, arg, NULL);
		else
			ft_export_error(arg);
	}
	else
	{
		key = ft_substr(arg, 0, ft_strchr(arg, '=') - arg);
		value = ft_strchr(arg, '=') + 1;
		if (ft_validate_identifier(key) == true)
		{
			ft_export_add(&ft_env->export, key, value);
			ft_export_add(&ft_env->env, key, value);
		}
		else
			ft_export_error(key);
		free(key);
	}
}

static void	ft_export_print(t_ft_env *ft_env, int fd)
{
	t_env	*iter;

	iter = ft_env->export;
	while (iter != NULL)
	{
		ft_fprintf(fd, "declare -x %s", iter->key, iter->value);
		if (iter->value != NULL)
		{
			ft_fprintf(fd, "=\"%s\"\n", iter->value);
		}
		else
		{
			ft_fprintf(fd, "\n");
		}
		iter = iter->next;
	}
	g_exit_status = 0;
}

void	ft_export(char **args, t_ft_env *ft_env, int fd)
{
	int	argc;
	int	i;

	argc = ft_count_args(args);
	if (argc == 1)
	{
		ft_export_print(ft_env, fd);
	}
	else
	{
		i = 1;
		while (args[i] != NULL)
		{
			ft_export_set(args[i], ft_env);
			g_exit_status = 0;
			++i;
		}
	}
}
