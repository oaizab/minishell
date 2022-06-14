/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 14:52:51 by hhamza            #+#    #+#             */
/*   Updated: 2022/06/14 17:30:41 by oaizab           ###   ########.fr       */
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

static void	ft_lexer_helper(const char *cmd, char **token_str, t_state state, \
	t_toklist **toklist)
{
	int				i;
	t_token_type	type;

	i = -1;
	while (cmd[++i] != '\0')
	{
		type = ft_get_token_type(&cmd[i]);
		if (state == STATE_DEFAULT)
		{
			if (type == TOKEN_WORD)
				*token_str = ft_append_char(*token_str, cmd[i]);
			else if (type == TOKEN_DQUOTE || type == TOKEN_QUOTE)
				ft_check_quote_tokens(type, token_str, cmd[i], &state);
			else
				ft_default_state(toklist, type, token_str, &i);
		}
		else
			ft_quote_state(&state, token_str, type, cmd[i]);
	}
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
	ft_lexer_helper(cmd, &token_str, state, &toklist);
	ft_add_token(&toklist, &token_str, TOKEN_WORD);
	return (ft_token_end(&toklist), toklist);
}
