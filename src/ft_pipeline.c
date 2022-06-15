/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipeline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:57:24 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/15 08:06:13 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Helper function for ft_parse_pipeline.
 *
 * @param scanner: Scanner object.
 * @param pipeline: Pipeline node.
 * @param pipetmp: Temporary pipeline node address.
 * @return bool: false if ft_parse_pipeline shall return NULL, true otherwise.
 */
static bool	ft_parse_pipeline_helper(t_scanner *scanner, t_ast_node *pipeline, \
	t_ast_node **pipetmp)
{
	t_ast_node	*cmdtmp;

	while (ft_scanner_peek(scanner)->type == TOKEN_PIPE)
	{
		get_next_token(scanner);
		if (!ft_is_command(ft_scanner_peek(scanner)->type))
			return (ft_ast_free(pipeline), ft_error(ERR_SYNTAX, \
				ft_scanner_peek(scanner)), false);
		cmdtmp = ft_parse_command(scanner);
		if (cmdtmp == NULL)
			return (ft_ast_free(pipeline), NULL);
		if (ft_scanner_peek(scanner)->type == TOKEN_PIPE)
		{
			(*pipetmp)->right = ft_ast_node_new(NODE_PIPE, NULL);
			if ((*pipetmp)->right == NULL)
				return (ft_ast_free(pipeline), ft_error(ERR_MALLOC, 0), false);
			*pipetmp = (*pipetmp)->right;
			(*pipetmp)->left = cmdtmp;
		}
		else
			(*pipetmp)->right = cmdtmp;
	}
	return (true);
}

/**
 * @brief Parse pipeline.
 *
 * @param scanner: Scanner object.
 * @return t_ast_node*: Pipeline node, NULL on failure.
 */
t_ast_node	*ft_parse_pipeline(t_scanner *scanner)
{
	t_ast_node	*pipeline;
	t_ast_node	*pipetmp;
	t_ast_node	*cmdtmp;

	if (!ft_is_command(ft_scanner_peek(scanner)->type))
		return (ft_error(ERR_SYNTAX, ft_scanner_peek(scanner)), NULL);
	cmdtmp = ft_parse_command(scanner);
	if (cmdtmp != NULL && ft_scanner_peek(scanner)->type == TOKEN_PIPE)
	{
		pipeline = ft_ast_node_new(NODE_PIPE, NULL);
		if (pipeline == NULL)
			return (ft_ast_free(cmdtmp), ft_error(ERR_MALLOC, NULL), NULL);
		pipetmp = pipeline;
		pipeline->left = cmdtmp;
	}
	else
		return (cmdtmp);
	if (ft_parse_pipeline_helper(scanner, pipeline, &pipetmp) == false)
		return (NULL);
	else
		return (pipeline);
}
