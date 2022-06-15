/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_block.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 16:40:41 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/15 15:07:40 by oaizab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Test if token is a block (&& or ||)
 *
 * @param type: Token type.
 * @return bool: True if token is a block, false otherwise.
 */
static bool	ft_is_block(t_token_type type)
{
	return (type == TOKEN_AND || type == TOKEN_OR);
}

/**
 * @brief Get block token type (&& or ||)
 *
 * @param type: Token type.
 * @return t_node_type: Block type.
 */
static t_node_type	ft_get_block_type(t_token_type type)
{
	if (type == TOKEN_AND)
		return (NODE_AND);
	else
		return (NODE_OR);
}

/**
 * @brief Helper function for ft_parse_block.
 *
 * @param scanner: Scanner object.
 * @param block: Block node.
 * @param blocktmp: Temporary block node.
 * @return bool: false if ft_parse_block shall return NULL, true otherwise.
 */
static bool	ft_parse_block_helper(t_scanner *scanner, t_ast_node *block, \
	t_ast_node **blocktmp)
{
	t_ast_node	*pipetmp;

	while (ft_is_block(ft_scanner_peek(scanner)->type))
	{
		block = *blocktmp;
		get_next_token(scanner);
		if (!ft_is_command(ft_scanner_peek(scanner)->type))
			return (ft_ast_free(block), \
				ft_error(ERR_SYNTAX, ft_scanner_peek(scanner)), false);
		pipetmp = ft_parse_pipeline(scanner);
		if (pipetmp == NULL)
			return (ft_ast_free(block), false);
		if (ft_is_block(ft_scanner_peek(scanner)->type))
		{
			(*blocktmp) = ft_ast_node_new(ft_get_block_type(\
				ft_scanner_peek(scanner)->type), NULL);
			if ((*blocktmp) == NULL)
				return (ft_ast_free(block), false);
			(*blocktmp)->left = block;
			block->right = pipetmp;
		}
		else
			(*blocktmp)->right = pipetmp;
	}
	return (true);
}

/**
 * @brief Parse a block (&& or ||)
 *
 * @param scanner: Scanner object.
 * @return t_ast_node*: Block node, NULL on failure.
 */
t_ast_node	*ft_parse_block(t_scanner *scanner)
{
	t_ast_node	*block;
	t_ast_node	*blocktmp;
	t_ast_node	*pipetmp;

	if (!ft_is_command(ft_scanner_peek(scanner)->type))
		return (ft_error(ERR_SYNTAX, ft_scanner_peek(scanner)), NULL);
	pipetmp = ft_parse_pipeline(scanner);
	if (pipetmp != NULL && ft_is_block(ft_scanner_peek(scanner)->type))
	{
		block = ft_ast_node_new(ft_get_block_type(\
			ft_scanner_peek(scanner)->type), NULL);
		if (block == NULL)
			return (ft_ast_free(pipetmp), ft_error(ERR_MALLOC, NULL), NULL);
		blocktmp = block;
		block->left = pipetmp;
	}
	else
		return (pipetmp);
	if (ft_parse_block_helper(scanner, block, &blocktmp) == false)
		return (NULL);
	else
		return (blocktmp);
}
