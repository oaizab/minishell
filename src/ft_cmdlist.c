/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 09:21:27 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/13 10:24:15 by oaizab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*ft_parse_cmdlist(t_scanner *scanner)
{
	t_ast_node	*cmdlist;
	t_ast_node	*cmdtmp;
	t_token		*token;
	int			i;

	if (!ft_is_redir(ft_scanner_peek(scanner)->type) && ft_scanner_peek(scanner)->type != TOKEN_WORD)
		return (NULL);
	cmdlist = ft_ast_node_new(NODE_NOCMD, NULL);
	if (cmdlist == NULL)
		return (NULL);
	cmdtmp = cmdlist;
	if (ft_is_redir(ft_scanner_peek(scanner)->type))
	{
		cmdlist->left = ft_parse_redir(scanner);
		if (cmdlist->left == NULL)
			return (NULL);
		cmdlist = cmdlist->left;
	}
	if (ft_scanner_peek(scanner)->type == TOKEN_WORD)
	{
		i = 1;
		token = get_next_token(scanner);
		cmdtmp->value = ft_strdup(token->lexeme);
		cmdtmp->type = NODE_CMD;
		cmdtmp->args[0] = ft_strdup(token->lexeme);
		if (ft_is_redir(ft_scanner_peek(scanner)->type))
		{
			cmdlist->left = ft_parse_redir(scanner);
			if (cmdlist->left == NULL)
				return (NULL);
			cmdlist = cmdlist->left;
		}
		while (ft_scanner_peek(scanner)->type == TOKEN_WORD)
		{
			token = get_next_token(scanner);
			cmdtmp->args[i++] = ft_strdup(token->lexeme);
			if (ft_is_redir(ft_scanner_peek(scanner)->type))
			{
				cmdlist->left = ft_parse_redir(scanner);
				if (cmdlist->left == NULL)
					return (NULL);
				cmdlist = cmdlist->left;
			}
		}
	}
	return (cmdtmp);
}