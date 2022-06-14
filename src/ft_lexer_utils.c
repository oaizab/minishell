/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 17:15:02 by hhamza            #+#    #+#             */
/*   Updated: 2022/06/14 17:16:29 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Helper function for default state
 *
 * @param toklist: Token list address
 * @param type: Current token type
 * @param token_str: Token string address
 * @param i: Current character index
 */
void	ft_default_state(t_toklist **toklist, t_token_type type, \
	char **token_str, int *i)
{
	if (type == TOKEN_SPACE)
		ft_add_token(toklist, token_str, TOKEN_WORD);
	else if (type == TOKEN_PIPE)
		ft_separator_token(toklist, token_str, TOKEN_PIPE, "|");
	else if (type == TOKEN_OR)
		(ft_separator_token(toklist, token_str, TOKEN_OR, "||"), ++(*i));
	else if (type == TOKEN_AND)
		(ft_separator_token(toklist, token_str, TOKEN_AND, "&&"), ++(*i));
	else if (type == TOKEN_IN)
		ft_separator_token(toklist, token_str, TOKEN_IN, "<");
	else if (type == TOKEN_OUT)
		ft_separator_token(toklist, token_str, TOKEN_OUT, ">");
	else if (type == TOKEN_HEREDOC)
		(ft_separator_token(toklist, token_str, TOKEN_HEREDOC, "<<"), ++(*i));
	else if (type == TOKEN_APPEND)
		(ft_separator_token(toklist, token_str, TOKEN_APPEND, ">>"), ++(*i));
	else if (type == TOKEN_OPAR)
		ft_separator_token(toklist, token_str, TOKEN_OPAR, "(");
	else if (type == TOKEN_CPAR)
		ft_separator_token(toklist, token_str, TOKEN_CPAR, ")");
}

void	ft_token_end(t_toklist **toklist)
{
	t_token	*tokptr;

	tokptr = ft_calloc(1, sizeof(t_token));
	tokptr->lexeme = ft_strdup("newline");
	tokptr->type = TOKEN_END;
	ft_lstadd_back(toklist, ft_lstnew(tokptr));
}
