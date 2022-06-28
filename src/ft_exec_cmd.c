/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:43:36 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/28 13:23:41 by oaizab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_expand_command(t_ast_node *root, t_env *env)
{
	char	*tmp;

	if (root->type == NODE_CMD || (root->type == NODE_REDIR \
		&& root->redir_type != REDIR_HEREDOC))
	{
		tmp = ft_strdup(root->value);
		ft_expander(root, env);
		if (root->type == NODE_REDIR && root->args[1] != NULL)
		{
			ft_fprintf(2, "minishell: %s: ambiguous redirect\n", tmp);
			free(tmp);
			return (false);
		}
		free(tmp);
	}
	else if (root->type == NODE_REDIR && root->redir_type == REDIR_HEREDOC)
	{
		ft_heredoc_expander(root, env);
	}
	if (root->left)
		return (ft_expand_command(root->left, env));
	return (true);
}

bool	ft_find_command(t_ast_node *node, t_env *env)
{
	char	*path;
	char	**where;
	char	*tmp;
	int		i;

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
		if (access(tmp, F_OK) == 0)
		{
			free(node->value);
			ft_free_str_array(where);
			node->value = tmp;
			if (access(node->value, X_OK) == 0)
				return (true);
			else
			{
				g_exit_status = 126;
				return (ft_fprintf(2, "minishell: %s: Permission denied\n", node->value), false);
			}
			return (true);
		}
		else
			free(tmp);
		i++;
	}
	g_exit_status = 127;
	ft_free_str_array(where);
	ft_fprintf(2, "minishell: %s: command not found\n", node->value);
	return (false);
}

bool	ft_check_command(t_ast_node *node, t_env *env)
{
	if (ft_is_builtin(node->value))
		return (false);
	if (node->value[0] != '/' && ft_strncmp(node->value, "./", 2) != 0)
		return (ft_find_command(node, env));
	if (access(node->value, F_OK) == 0)
	{
		if (access(node->value, X_OK) == 0)
			return (true);
		else
		{
			g_exit_status = 126;
			return (ft_fprintf(2, "minishell: %s: Permission denied\n", node->value), false);
		}
		return (true);
	}
	g_exit_status = 127;
	ft_fprintf(2, "minishell: %s: No sush file or directory\n", node->value);
	return (false);
}

void	ft_execute_cmd(t_ast_node *node, t_ft_env *env)
{
	char	**envp;

	if (!ft_expand_command(node, env->env))
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
	if (ft_check_command(node, env->env))
	{
		if (fork() == 0)
		{
			ft_restore_ctrl_c();
			envp = ft_env_to_array(env->env);
			ft_uninstall_signals();
			dup2(node->in, STDIN_FILENO);
			dup2(node->out, STDOUT_FILENO);
			if (node->in != STDIN_FILENO)
				close(node->in);
			if (node->out != STDOUT_FILENO)
				close(node->out);
			exit(execve(node->value, node->args, envp));
		}
	}
	else
	{
		ft_execute_builtin(node, env);
		if (node->in != STDIN_FILENO)
			close(node->in);
		if (node->out != STDOUT_FILENO)
			close(node->out);
	}
}