/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 13:46:53 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/28 10:24:31 by oaizab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_expand_command(t_ast_node *root, t_env *env);

void	ft_execute_commande(t_ast_node *node, t_ft_env *env)
{
	if (node->type == NODE_CMD)
	{
		ft_execute_cmd(node, env);
	}
	else if (node->type == NODE_SUBSHELL)
	{
		if (!ft_expand_command(node, env->env))
		{
			ft_execute_redir(node);
			return ;
		}
		ft_execute_redir(node);
		node->right->out = node->out;
		node->right->in = node->in;
		ft_executor(node->right, env);
	}
}

void	ft_execute_pipeline(t_ast_node *node, t_ft_env *env_s)
{
	t_ast_node	*tmp;
	int			pipefd[2];

	tmp = node;
	if (tmp->type == NODE_PIPE)
		tmp->left->in = tmp->in;
	if (node->type == NODE_CMD || node->type == NODE_SUBSHELL)
		ft_execute_commande(tmp, env_s);
	else if (node->type == NODE_PIPE)
	{
		if (pipe(pipefd) == -1)
		{
			ft_fprintf(2, "minishell: pipe: %s\n", strerror(errno));
			return ;
		}
		tmp->right->in = pipefd[0];
		tmp->left->out = pipefd[1];
		ft_execute_pipeline(tmp->left, env_s);
		close(pipefd[1]);
		ft_execute_pipeline(tmp->right, env_s);
		close(pipefd[0]);
	}
}

void ft_execute_block(t_ast_node *node, t_ft_env *env_s)
{
	t_ast_node	*tmp;

	tmp = node;
	if (tmp->left)
	{
		tmp->left->in = tmp->in;
		tmp->left->out = tmp->out;
	}
	if (tmp->right)
	{
		tmp->right->in = tmp->in;
		tmp->right->out = tmp->out;
	}
	if (tmp->type != NODE_AND && tmp->type != NODE_OR)
		ft_execute_pipeline(tmp, env_s);
	else if (tmp->type == NODE_AND)
	{
		ft_execute_block(tmp->left, env_s);
		ft_wait();
		if (g_exit_status == 0)
			ft_execute_block(tmp->right, env_s);
	}
	else if (tmp->type == NODE_OR)
	{
		ft_execute_block(tmp->left, env_s);
		ft_wait();
		if (g_exit_status != 0)
			ft_execute_block(tmp->right, env_s);
	}
}

static void	ft_execute(t_ast_node *root, t_ft_env *env_s)
{
	ft_execute_block(root, env_s);
}

void	ft_executor(t_ast_node *root, t_ft_env *env_s)
{
	t_env	*env;
	t_env	*export;

	env = env_s->env;
	export = env_s->export;
	if (!root)
		return ;
	if (root->type == NODE_REDIR)
		return ;
	ft_execute(root, env_s);
}
