/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 16:19:01 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/28 08:30:04 by oaizab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Create a new AST (Abstract Syntax Tree) node.
 *
 * @param type: AST node type.
 * @param value: AST node value (NULL for no value, e.g., and, or and pipes).
 * @return t_ast_node*:	Newly created AST node.
 */
t_ast_node	*ft_ast_node_new(t_node_type type, char *value)
{
	t_ast_node	*node;

	node = (t_ast_node *) ft_calloc(1, sizeof(t_ast_node));
	if (node == NULL)
		return (NULL);
	node->type = type;
	node->value = value;
	node->in = STDIN_FILENO;
	node->out = STDOUT_FILENO;
	return (node);
}

/**
 * @brief Display an AST (Abstract Syntax Tree).
 *
 * @param root: Root of the AST.
 */
void	display_ast(t_ast_node *root)
{
	int	i;

	if (root == NULL)
		return ;
	if (root->type == NODE_CMD)
	{
		ft_printf("%s ", root->value);
		i = 1;
		while (root->args[i] != NULL)
			ft_printf("[%s] ", root->args[i++]);
		ft_printf("\n");
	}
	else if (root->type == NODE_PIPE)
		ft_printf("|\n");
	else if (root->type == NODE_AND)
		ft_printf("&&\n");
	else if (root->type == NODE_OR)
		ft_printf("||\n");
	else if (root->type == NODE_REDIR && root->redir_type != REDIR_HEREDOC)
		ft_printf("redir %s\n", root->value);
	else if (root->type == NODE_REDIR && root->redir_type == REDIR_HEREDOC)
		ft_printf("<< %s", root->value);
	else if (root->type == NODE_NOCMD)
		ft_printf("NOCMD\n", root->value);
	(display_ast(root->left), display_ast(root->right));
}

/**
 * @brief Free AST (Abstract Syntax Tree).
 *
 * @param root: Root of the AST.
 */
void	ft_ast_free(t_ast_node *root)
{
	int	i;

	if (root == NULL)
		return ;
	if (root->value != NULL)
		free(root->value);
	i = 0;
	while (root->args && root->args[i])
		free(root->args[i++]);
	free(root->args);
	ft_ast_free(root->left);
	ft_ast_free(root->right);
	free(root);
}
