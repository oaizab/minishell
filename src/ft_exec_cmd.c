/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:43:36 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/30 09:19:45 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_access(t_ast_node *node, char *tmp, \
	char **where)
{
	if (access(tmp, F_OK) == 0)
	{
		free(node->value);
		free(node->args[0]);
		ft_free_str_array(where);
		node->value = tmp;
		node->args[0] = ft_strdup(node->value);
		if (access(node->value, X_OK) == 0)
			return (1);
		else
		{
			g_exit_status = 126;
			return (ft_fprintf(2, "minishell: %s: Permission denied\n", \
				node->value), 0);
		}
		return (1);
	}
	else
		free(tmp);
	return (2);
}

static bool	ft_find_command(t_ast_node *node, t_env *env)
{
	char	*path;
	char	**where;
	char	*tmp;
	int		i;
	int		ac;

	path = ft_env_get(env, "PATH");
	where = ft_split(path, ':');
	i = 0;
	while (where[i])
	{
		if (where[i][ft_strlen(where[i]) - 1] != '/')
			tmp = ft_strjoin(where[i], "/");
		else
			tmp = ft_strdup(where[i]);
		tmp = ft_append_str(tmp, node->value);
		ac = ft_check_access(node, tmp, where);
		if (ac != 2)
			return (ac);
		i++;
	}
	g_exit_status = 127;
	ft_free_str_array(where);
	ft_fprintf(2, "minishell: %s: command not found\n", node->value);
	return (false);
}

void	ft_underscore(t_ast_node *node, t_ft_env *env)
{
	int	i;

	i = 0;
	while (node->args[i + 1])
		i++;
	ft_env_add(&env->env, "_", node->args[i]);
}

static bool	ft_check_command(t_ast_node *node, t_ft_env *env)
{
	if (ft_is_builtin(node->value))
		return (false);
	if (node->value[0] != '/' && ft_strncmp(node->value, "./", 2) != 0 \
			&& ft_strncmp(node->value, "../", 3) != 0)
		return (ft_find_command(node, env->env));
	if (access(node->value, F_OK) == 0)
	{
		if (access(node->value, X_OK) == 0)
		{
			return (true);
		}
		else
		{
			g_exit_status = 126;
			return (ft_fprintf(2, "minishell: %s: Permission denied\n", \
				node->value), false);
		}
		return (true);
	}
	g_exit_status = 127;
	ft_fprintf(2, "minishell: %s: No sush file or directory\n", node->value);
	return (false);
}

void	ft_execute_cmd(t_ast_node *node, t_ft_env *env)
{
	if (!ft_expand_command(node, env->env) || node->type == NODE_REDIR)
	{
		ft_execute_redir(node);
		if (node->in != STDIN_FILENO)
			close(node->in);
		if (node->out != STDOUT_FILENO)
			close(node->out);
		return ;
	}
	ft_execute_redir(node);
	ft_signals_ign();
	if (ft_check_command(node, env))
		ft_execute_cmd_fork(node, env);
	else
	{
		ft_underscore(node, env);
		ft_execute_builtin(node, env);
		if (node->in != STDIN_FILENO)
			close(node->in);
		if (node->out != STDOUT_FILENO)
			close(node->out);
		ft_underscore(node, env);
	}
}
