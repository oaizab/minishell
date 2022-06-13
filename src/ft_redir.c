/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 16:54:58 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/13 09:17:54 by oaizab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_is_redir(t_token_type type)
{
	return (type == TOKEN_IN || type == TOKEN_OUT || type == TOKEN_APPEND \
		|| type == TOKEN_HEREDOC);
}

static t_redir_type get_redir_type(t_token_type type)
{
	if (type == TOKEN_IN)
		return (REDIR_IN);
	else if (type == TOKEN_OUT)
		return (REDIR_OUT);
	else if (type == TOKEN_APPEND)
		return (REDIR_APPEND);
	else
		return (REDIR_HEREDOC);
}

t_ast_node *ft_parse_redir(t_scanner *scanner)
{
	t_ast_node	*redir;
	t_token		*token;

	token = get_next_token(scanner);
	redir = NULL;
	if (ft_is_redir(token->type))
	{
		redir = ft_ast_node_new(NODE_REDIR, NULL);
		if (redir == NULL)
			return (NULL);
		redir->redir_type = get_redir_type(token->type);
		token = get_next_token(scanner);
		if (token->type == TOKEN_WORD)
		{
			redir->value = token->lexeme;
		}
		else
		{
			ft_error(ERR_SYNTAX, token);
			return (NULL);
		}
	}
	if (ft_is_redir(ft_scanner_peek(scanner)->type))
	{
		redir->left = ft_parse_redir(scanner);
		if (redir->left == NULL)
			return (NULL);
	}
	return (redir);
}
