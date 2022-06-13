/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 09:21:27 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/13 16:38:31 by oaizab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_is_cmdlist(t_token_type type)
{
	return (type == TOKEN_WORD || ft_is_redir(type));
}

static bool	ft_redirlist(t_scanner *scanner, t_ast_node **cmdlist)
{
	if (ft_is_redir(ft_scanner_peek(scanner)->type))
	{
		(*cmdlist)->left = ft_parse_redir(scanner);
		if ((*cmdlist)->left == NULL)
			return (false);
		while ((*cmdlist)->left != NULL)
			*cmdlist = (*cmdlist)->left;
	}
	return (true);
}

static bool	ft_cmdlist(t_scanner *scanner, t_ast_node **cmdlist, \
	t_ast_node **cmdtmp, int i)
{
	t_token		*token;

	if (ft_scanner_peek(scanner)->type == TOKEN_WORD)
	{
		token = get_next_token(scanner);
		(*cmdtmp)->value = ft_strdup(token->lexeme);
		(*cmdtmp)->type = NODE_CMD;
		(*cmdtmp)->args = ft_calloc(ARG_MAX, sizeof(char *));
		// TODO: check if calloc failed
		(*cmdtmp)->args[0] = ft_strdup(token->lexeme);
		if (!ft_redirlist(scanner, cmdlist))
			return (false);
		while (ft_scanner_peek(scanner)->type == TOKEN_WORD)
		{
			token = get_next_token(scanner);
			(*cmdtmp)->args[i++] = ft_strdup(token->lexeme);
			if (!ft_redirlist(scanner, cmdlist))
				return (false);
		}
	}
	return (true);
}

t_ast_node	*ft_parse_cmdlist(t_scanner *scanner)
{
	t_ast_node	*cmdlist;
	t_ast_node	*cmdtmp;

	cmdlist = ft_ast_node_new(NODE_NOCMD, NULL);
	if (cmdlist == NULL)
		return (NULL);
	cmdtmp = cmdlist;
	if (!ft_redirlist(scanner, &cmdlist))
		return (NULL);
	if (!ft_cmdlist(scanner, &cmdlist, &cmdtmp, 1))
		return (NULL);
	if (cmdtmp->type == NODE_NOCMD)
	{
		cmdlist = cmdtmp->left;
		// TODO: free inside cmdtmp
		return (free(cmdtmp), cmdlist);
	}
	return (cmdtmp);
}
