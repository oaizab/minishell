/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 14:52:51 by hhamza            #+#    #+#             */
/*   Updated: 2022/06/06 11:15:42 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Helper function for single/double quote state
 *
 */
static void	ft_quote_state(t_state *state, char **token_str, \
	t_token_type type, char curr_char)
{
	if (*state == STATE_DQUOTE)
	{
		*token_str = ft_append_char(*token_str, curr_char);
		if (type == TOKEN_DQUOTE)
			*state = STATE_DEFAULT;
	}
	else if (*state == STATE_QUOTE)
	{
		*token_str = ft_append_char(*token_str, curr_char);
		if (type == TOKEN_QUOTE)
			*state = STATE_DEFAULT;
	}
}

/**
 * @brief Helper function to check if the current character is a single/double
 * quote
 *
 * @param type: Current token type
 * @param token_str: Current token string address
 * @param curr_char: Current character
 * @param state: Current state
 */
static void	ft_check_quote_tokens(t_token_type type, char **token_str, \
	char curr_char, t_state *state)
{
	if (type == TOKEN_DQUOTE)
	{
		*token_str = ft_append_char(*token_str, curr_char);
		*state = STATE_DQUOTE;
	}
	else if (type == TOKEN_QUOTE)
	{
		*token_str = ft_append_char(*token_str, curr_char);
		*state = STATE_QUOTE;
	}
}

/**
 * @brief Helper function to run when finding a separator token (pipe,
 * redirection, and, or, parentheses, ...)
 *
 * @param toklist: Token list address
 * @param token_str: Token string address
 * @param type: Current token type
 * @param token_val: Token value
 */
static void	ft_separator_token(t_toklist **toklist, char **token_str, \
	t_token_type type, char *token_val)
{
	ft_add_token(toklist, token_str, TOKEN);
	*token_str = ft_append_str(*token_str, token_val);
	ft_add_token(toklist, token_str, type);
}

/**
 * @brief Helper function for default state
 *
 * @param toklist: Token list address
 * @param type: Current token type
 * @param token_str: Token string address
 * @param i: Current character index
 */
static void	ft_default_state(t_toklist **toklist, t_token_type type, \
	char **token_str, int *i)
{
	if (type == TOKEN_SPACE)
		ft_add_token(toklist, token_str, TOKEN);
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

/**
 * @brief Minishell lexer. Splits input command into a list of tokens
 *
 * @param cmd: Input command string
 * @return t_toklist*: Newly generated token list
 */
t_toklist	*ft_lexer(const char *cmd)
{
	int						i;
	t_state					state;
	t_token_type			type;
	char					*token_str;
	static t_toklist		*toklist;

	token_str = NULL;
	state = STATE_DEFAULT;
	i = -1;
	while (cmd[++i] != '\0')
	{
		type = ft_get_token_type(&cmd[i]);
		if (state == STATE_DEFAULT)
		{
			if (type == TOKEN_DEFAULT)
				token_str = ft_append_char(token_str, cmd[i]);
			else if (type == TOKEN_DQUOTE || type == TOKEN_QUOTE)
				ft_check_quote_tokens(type, &token_str, cmd[i], &state);
			else
				ft_default_state(&toklist, type, &token_str, &i);
		}
		else
			ft_quote_state(&state, &token_str, type, cmd[i]);
	}
	return (ft_add_token(&toklist, &token_str, TOKEN), toklist);
}
