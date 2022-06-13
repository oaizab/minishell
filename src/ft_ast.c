/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 16:19:01 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/13 10:15:01 by oaizab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*ft_ast_node_new(t_node_type type, char *value)
{
	t_ast_node	*node;

	node = (t_ast_node *) ft_calloc(1, sizeof(t_ast_node));
	if (node == NULL)
		return (NULL);
	node->type = type;
	node->value = value;
	return (node);
}

void	ft_insert_child(t_ast_node *root, t_ast_node *left ,t_ast_node *right)
{
	if (root == NULL)
		return ;
	root->left = left;
	root->right = right;
}

void	display_ast(t_ast_node *root)
{
	if (root == NULL)
		return ;
	if (root->type == NODE_CMD)
	{
		ft_printf("%s ", root->value);
		for (int i = 1; root->args[i] != NULL; i++)
		{
			ft_printf("%s ", root->args[i]);
		}
		ft_printf("\n");
	}
	else if (root->type == NODE_PIPE)
		ft_printf("|\n");
	else if (root->type == NODE_AND)
		ft_printf("&&\n");
	else if (root->type == NODE_OR)
		ft_printf("||\n");
	else if (root->type == NODE_REDIR)
		ft_printf("redir %s\n", root->value);
	else if (root->type == NODE_NOCMD)
		ft_printf("NOCMD\n", root->value);
	display_ast(root->left);
	display_ast(root->right);
}
