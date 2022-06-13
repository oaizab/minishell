/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipeline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:57:24 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/13 15:58:48 by oaizab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*ft_parse_pipeline(t_scanner *scanner)
{
	t_ast_node	*pipeline;
	t_ast_node	*pipetmp;
	t_ast_node	*cmdtmp;

	if (!ft_is_command(ft_scanner_peek(scanner)->type))
		return (ft_error(ERR_SYNTAX, ft_scanner_peek(scanner)), NULL);
	cmdtmp = ft_parse_command(scanner);
	if (ft_scanner_peek(scanner)->type == TOKEN_PIPE)
	{
		pipeline = ft_ast_node_new(NODE_PIPE, NULL);
		pipetmp = pipeline;
		pipeline->left = cmdtmp;
	}
	else
		return (cmdtmp);
	while (ft_scanner_peek(scanner)->type == TOKEN_PIPE)
	{
		get_next_token(scanner);
		if (!ft_is_command(ft_scanner_peek(scanner)->type))
			return (ft_error(ERR_SYNTAX, ft_scanner_peek(scanner)), NULL);
		cmdtmp = ft_parse_command(scanner);
		if (!cmdtmp)
			return (NULL);
		if (ft_scanner_peek(scanner)->type == TOKEN_PIPE)
		{
			pipetmp->right = ft_ast_node_new(NODE_PIPE, NULL);
			pipetmp = pipetmp->right;
			pipetmp->left = cmdtmp;
		}
		else
			pipetmp->right = cmdtmp;
	}
	return (pipeline);
}
