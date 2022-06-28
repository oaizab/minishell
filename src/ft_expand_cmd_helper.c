/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_cmd_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:23:13 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/28 18:28:52 by oaizab           ###   ########.fr       */
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

void	ft_execute_cmd_fork(t_ast_node *node, t_ft_env *env)
{
	char	**envp;

	ft_underscore(node, env);
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
