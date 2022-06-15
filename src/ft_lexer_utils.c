/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 17:15:02 by hhamza            #+#    #+#             */
/*   Updated: 2022/06/15 11:56:41 by oaizab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Helper function to run when finding a separator token (pipe,
 * redirection, and, or, parentheses, ...)
 *
 * @param toklist: Token list address
 * @param token_str: Token string address
 * @param type: Current token type
 * @param token_val: Token value
 */
static bool	ft_separator_token(t_toklist **toklist, char **token_str, \
	t_token_type type, char *token_val)
{
	if (!ft_add_token(toklist, token_str, TOKEN_WORD))
		return (false);
	*token_str = ft_append_str(*token_str, token_val);
	if (!ft_add_token(toklist, token_str, type))
		return (false);
	return (true);
}

static bool	ft_default_state_helper(t_toklist **toklist, t_token_type type, \
	char **token_str, int *i)
{
	if (type == TOKEN_OUT)
		return (ft_separator_token(toklist, token_str, TOKEN_OUT, ">"));
	else if (type == TOKEN_HEREDOC)
	{
		++(*i);
		return (ft_separator_token(toklist, token_str, TOKEN_HEREDOC, "<<"));
	}
	else if (type == TOKEN_APPEND)
	{
		++(*i);
		return (ft_separator_token(toklist, token_str, TOKEN_APPEND, ">>"));
	}
	else if (type == TOKEN_OPAR)
		return (ft_separator_token(toklist, token_str, TOKEN_OPAR, "("));
	else if (type == TOKEN_CPAR)
		return (ft_separator_token(toklist, token_str, TOKEN_CPAR, ")"));
	return (true);
}

/**
 * @brief Helper function for default state
 *
 * @param toklist: Token list address
 * @param type: Current token type
 * @param token_str: Token string address
 * @param i: Current character index
 */
bool	ft_default_state(t_toklist **toklist, t_token_type type, \
	char **token_str, int *i)
{
	if (type == TOKEN_SPACE)
		return (ft_add_token(toklist, token_str, TOKEN_WORD));
	else if (type == TOKEN_PIPE)
		return (ft_separator_token(toklist, token_str, TOKEN_PIPE, "|"));
	else if (type == TOKEN_OR)
	{
		++(*i);
		return (ft_separator_token(toklist, token_str, TOKEN_OR, "||"));
	}
	else if (type == TOKEN_AND)
	{
		++(*i);
		return (ft_separator_token(toklist, token_str, TOKEN_AND, "&&"));
	}
	else if (type == TOKEN_IN)
		return (ft_separator_token(toklist, token_str, TOKEN_IN, "<"));
	else
		return (ft_default_state_helper(toklist, type, token_str, i));
}

/**
 * @brief Add END token to token list.
 *
 * @param toklist: Token list address
 */
void	ft_token_end(t_toklist **toklist)
{
	t_token	*tokptr;
	t_list	*new;

	tokptr = ft_calloc(1, sizeof(t_token));
	if (!tokptr)
	{
		ft_lstclear(toklist, &ft_token_destroy);
		*toklist = NULL;
	}
	tokptr->lexeme = ft_strdup("newline");
	if (!tokptr->lexeme)
	{
		(ft_lstclear(toklist, &ft_token_destroy), free(tokptr));
		*toklist = NULL;
	}
	tokptr->type = TOKEN_END;
	new = ft_lstnew(tokptr);
	if (!new)
	{
		(ft_lstclear(toklist, &ft_token_destroy), ft_token_destroy(tokptr));
		*toklist = NULL;
	}
	ft_lstadd_back(toklist, new);
}
