/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 14:52:51 by hhamza            #+#    #+#             */
/*   Updated: 2022/06/15 12:51:21 by oaizab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Helper function for single/double quote state
 *
 * @param state: Current state address.
 * @param token_str: Current token string address.
 * @param type: Current token type.
 * @param curr_char: Current character.
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

static bool	ft_lexer_helper_helper(t_token_type type, char **token_str, \
	char curr_char, t_state *state)
{
	if (type == TOKEN_WORD)
	{
		*token_str = ft_append_char(*token_str, curr_char);
		return (true);
	}
	else if (type == TOKEN_DQUOTE || type == TOKEN_QUOTE)
	{
		ft_check_quote_tokens(type, token_str, curr_char, state);
		return (true);
	}
	return (false);
}

/**
 * @brief Helper function for ft_lexer.
 *
 * @param cmd: Input command string.
 * @param token_str: Current token string address.
 * @param state: Current state.
 * @param toklist: Token list address.
 */
static bool	ft_lexer_helper(const char *cmd, char **token_str, t_state *state, \
	t_toklist **toklist)
{
	int				i;
	t_token_type	type;
	bool			is_token;

	i = -1;
	while (cmd[++i] != '\0')
	{
		is_token = false;
		type = ft_get_token_type(&cmd[i]);
		if (*state == STATE_DEFAULT)
		{
			if (!ft_lexer_helper_helper(type, token_str, cmd[i], state))
			{
				if (!ft_default_state(toklist, type, token_str, &i))
					return (false);
				is_token = true;
			}
		}
		else
			ft_quote_state(state, token_str, type, cmd[i]);
		if (!is_token && *token_str == NULL)
			return (false);
	}
	return (true);
}

/**
 * @brief Minishell lexer. Splits input command into a list of tokens
 *
 * @param cmd: Input command string
 * @return t_toklist*: Newly generated token list
 */
t_toklist	*ft_lexer(const char *cmd)
{
	t_state			state;
	char			*token_str;
	t_toklist		*toklist;

	token_str = NULL;
	state = STATE_DEFAULT;
	toklist = NULL;
	if (!ft_lexer_helper(cmd, &token_str, &state, &toklist))
		return (ft_lstclear(&toklist, &ft_token_destroy), NULL);
	if (!ft_add_token(&toklist, &token_str, TOKEN_WORD))
		return (ft_lstclear(&toklist, &ft_token_destroy), NULL);
	if (state == STATE_DQUOTE || state == STATE_QUOTE)
		return (ft_error(ERR_QUOTE, NULL), ft_lstclear(&toklist, \
			&ft_token_destroy), NULL);
	return (ft_token_end(&toklist), toklist);
}
