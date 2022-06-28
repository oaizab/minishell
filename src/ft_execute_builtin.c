/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_builtin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 19:16:37 by hhamza            #+#    #+#             */
/*   Updated: 2022/06/28 09:35:50 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_is_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "echo") == 0 \
		|| ft_strcmp(cmd, "cd") == 0 \
		|| ft_strcmp(cmd, "pwd") == 0 \
		|| ft_strcmp(cmd, "export") == 0 \
		|| ft_strcmp(cmd, "unset") == 0 \
		|| ft_strcmp(cmd, "env") == 0 \
		|| ft_strcmp(cmd, "exit") == 0);
}

bool	ft_execute_builtin(t_ast_node *root, t_ft_env *ft_env)
{
	if (ft_is_builtin(root->value) == false)
	{
		return (false);
	}
	if (ft_strcmp(root->value, "echo") == 0)
		g_exit_status = ft_echo(root->args, root->out);
	else if (ft_strcmp(root->value, "cd") == 0)
		g_exit_status = ft_cd(root->args, &ft_env->env, root->out);
	else if (ft_strcmp(root->value, "pwd") == 0)
		g_exit_status = ft_pwd(STDOUT_FILENO);
	else if (ft_strcmp(root->value, "export") == 0)
		ft_export(root->args, ft_env, root->out);
	else if (ft_strcmp(root->value, "unset") == 0)
		g_exit_status = ft_unset(root->args, ft_env);
	return (true);
}
