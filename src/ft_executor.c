/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 13:46:53 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/27 17:07:10 by oaizab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute_pipeline(t_ast_node *node, t_env *env)
{
	t_ast_node	*tmp;
	int			pipefd[2];

	tmp = node;
	if (tmp->type == NODE_PIPE)
		tmp->left->in = tmp->in;
	if (node->type == NODE_CMD)
		ft_execute_cmd(tmp, env);
	else if (node->type == NODE_PIPE)
	{
		if (pipe(pipefd) == -1)
		{
			ft_fprintf(2, "minishell: pipe: %s\n", strerror(errno));
			return ;
		}
		tmp->right->in = pipefd[0];
		tmp->left->out = pipefd[1];
		ft_execute_pipeline(tmp->left, env);
		close(pipefd[1]);
		ft_execute_pipeline(tmp->right, env);
		close(pipefd[0]);
	}
}

static void	ft_execute(t_ast_node *root, t_env *env, t_env *export)
{
	(void) export;
	ft_execute_pipeline(root, env);
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
	ft_execute(root, env, export);
	if (root->type == NODE_PIPE)
		return ;
	ft_executor(root->left, env_s);
	ft_executor(root->right, env_s);
}
