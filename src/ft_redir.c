/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 16:54:58 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/16 12:52:07 by oaizab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Test if token is a redirection,
 *
 * @param type: Token type.
 * @return bool: True if token is a redirection, false otherwise.
 */
bool	ft_is_redir(t_token_type type)
{
	return (type == TOKEN_IN || type == TOKEN_OUT || type == TOKEN_APPEND \
		|| type == TOKEN_HEREDOC);
}

/**
 * @brief Get the redirection type.
 *
 * @param type: Redirection token type.
 * @return t_redir_type: Redirection type (Input, output, append or heredoc).
 */
static t_redir_type	get_redir_type(t_token_type type)
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

static bool	ft_check_heredoc(t_ast_node **redir, t_token *token, \
	t_ast_node **redirtmp)
{
	if ((*redir)->redir_type != REDIR_HEREDOC)
	{
		(*redir)->value = ft_strdup(token->lexeme);
	}
	else
		(*redir)->value = ft_heredoc(token->lexeme);
	if ((*redir)->value == NULL)
		return (ft_ast_free(*redirtmp), ft_error(ERR_MALLOC, 0), false);
	return (true);
}

/**
 * @brief Helper function for ft_parse_redir.
 *
 * @param scanner: Scanner object.
 * @param redir: Redicrection node addess.
 * @param redirtmp: Redirection temporary node address.
 * @return bool: false if ft_parse_redir shall return NULL, true otherwise.
 */
static bool	ft_parse_redir_helper(t_scanner *scanner, t_ast_node **redir, \
	t_ast_node **redirtmp)
{
	t_token	*token;

	if (ft_is_redir(ft_scanner_peek(scanner)->type))
	{
		token = get_next_token(scanner);
		*redir = ft_ast_node_new(NODE_REDIR, NULL);
		if (*redir == NULL)
			return (ft_error(ERR_MALLOC, NULL), false);
		*redirtmp = *redir;
		(*redir)->redir_type = get_redir_type(token->type);
		token = get_next_token(scanner);
		if (token->type == TOKEN_WORD)
		{
			if (!ft_check_heredoc(redir, token, redirtmp))
				return (false);
		}
		else
			return (ft_ast_free(*redirtmp), ft_error(ERR_SYNTAX, token), false);
	}
	return (true);
}

/**
 * @brief Parse redirection.
 *
 * @param scanner: Scanner object.
 * @return t_ast_node*: Redirection node, NULL otherwise.
 */
t_ast_node	*ft_parse_redir(t_scanner *scanner)
{
	t_ast_node	*redir;
	t_ast_node	*redirtmp;
	t_token		*token;

	redir = NULL;
	if (ft_parse_redir_helper(scanner, &redir, &redirtmp) == false)
		return (NULL);
	while (ft_is_redir(ft_scanner_peek(scanner)->type))
	{
		token = get_next_token(scanner);
		redir->left = ft_ast_node_new(NODE_REDIR, NULL);
		if (redir->left == NULL)
			return (ft_ast_free(redirtmp), NULL);
		redir = redir->left;
		redir->redir_type = get_redir_type(token->type);
		token = get_next_token(scanner);
		if (token->type == TOKEN_WORD)
		{
			if (!ft_check_heredoc(&redir, token, &redirtmp))
				return (false);
		}
		else
			return (ft_ast_free(redirtmp), ft_error(ERR_SYNTAX, token), NULL);
	}
	return (redirtmp);
}
