/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_block.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 16:40:41 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/13 16:47:39 by oaizab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool ft_is_block(t_token_type type)
{
	return (type == TOKEN_AND || type == TOKEN_OR);
}

static t_node_type	ft_get_block_type(t_token_type type)
{
	if (type == TOKEN_AND)
		return (NODE_AND);
	else
		return (NODE_OR);
}

t_ast_node	*ft_parse_block(t_scanner *scanner)
{
	t_ast_node	*block;
	t_ast_node	*blocktmp;
	t_ast_node	*pipetmp;

	if (!ft_is_command(ft_scanner_peek(scanner)->type))
		return (ft_error(ERR_SYNTAX, ft_scanner_peek(scanner)), NULL);
	pipetmp = ft_parse_pipeline(scanner);
	if (ft_is_block(ft_scanner_peek(scanner)->type))
	{
		block = ft_ast_node_new(ft_get_block_type( \
			ft_scanner_peek(scanner)->type), NULL);
		blocktmp = block;
		block->left = pipetmp;
	}
	else
		return (pipetmp);
	while (ft_is_block(ft_scanner_peek(scanner)->type))
	{
		get_next_token(scanner);
		if (!ft_is_command(ft_scanner_peek(scanner)->type))
			return (ft_error(ERR_SYNTAX, ft_scanner_peek(scanner)), NULL);
		pipetmp = ft_parse_pipeline(scanner);
		if (!pipetmp)
			return (NULL);
		if (ft_is_block(ft_scanner_peek(scanner)->type))
		{
			blocktmp->right = ft_ast_node_new(ft_get_block_type( \
				ft_scanner_peek(scanner)->type), NULL);
			blocktmp = blocktmp->right;
			blocktmp->left = pipetmp;
		}
		else
			blocktmp->right = pipetmp;
	}
	return (block);
}
