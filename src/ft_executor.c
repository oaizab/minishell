/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 13:46:53 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/22 18:28:40 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_execute(t_ast_node *root, t_env *env, t_env *export)
{
	(void) export;
	if (root->type == NODE_CMD || (root->type == NODE_REDIR \
		&& root->redir_type != REDIR_HEREDOC))
	{
		ft_expander(root, env);
	}
	else if (root->type == NODE_REDIR && root->redir_type == REDIR_HEREDOC)
	{
		ft_heredoc_expander(root, env);
	}
}

void	ft_executor(t_ast_node *root, t_env *env, t_env *export)
{
	(void) export;
	if (!root)
		return ;
	ft_execute(root, env, export);
	ft_executor(root->left, env, export);
	ft_executor(root->right, env, export);
}
