/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:39:15 by oaizab            #+#    #+#             */
/*   Updated: 2022/05/24 17:58:09 by oaizab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_char_type	get_char_type(const char *c)
{
	if (!c || c[0] == '\0')
		return (-1);
	if (c[0] == '&' && c[1] != '\0' && c[1] == '&')
		return (CHAR_AND);
	if (c[0] == '|' && c[1] != '\0' && c[1] == '|')
		return (CHAR_OR);
	if (c[0] == '|')
		return (CHAR_PIPE);
	if (c[0] == '<' && c[1] != '\0' && c[1] == '<')
		return (CHAR_HEREDOC);
	if (c[0] == '<')
		return (CHAR_IN);
	if (c[0] == '>' && c[1] != '\0' && c[1] == '>')
		return (CHAR_APPEND);
	if (c[0] == '>')
		return (CHAR_OUT);
	if (c[0] == '\'')
		return (CHAR_QUOTE);
	if (c[0] == '"')
		return (CHAR_DQUOTE);
	if (c[0] == ' ')
		return (CHAR_SPACE);
	return (CHAR_DEFAULT);
}

t_token	*ft_token_init(char *str, t_char_type type)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->tok = str;
	token->type = type;
	return (token);
}

void	in_quotes(t_state *state, char **token_str, t_char_type type ,char curr_char)
{
	if (*state == STATE_DQUOTE)
	{
		*token_str = ft_append_char(*token_str, curr_char);
		if (type == CHAR_DQUOTE)
			*state = STATE_DEFAULT;
	}
	else if (*state == STATE_QUOTE)
	{
		*token_str = ft_append_char(*token_str, curr_char);
		if (type == CHAR_QUOTE)
			*state = STATE_DEFAULT;
	}
}

void	add_token(t_toklist **toklist, char **token_str, t_char_type type)
{
	t_token	*token;

	if (*token_str != NULL)
	{
		token = ft_token_init(*token_str, type);
		ft_lstadd_back(toklist, ft_lstnew(token));
		token = NULL;
		*token_str = NULL;
	}
}

t_toklist	*ft_lexer(const char *cmd)
{
	int			i;
	t_state		state;
	t_char_type	type;
	char		*token_str;
	t_toklist	*toklist;

	if (cmd == NULL)
		return (NULL);
	token_str = NULL;
	state = STATE_DEFAULT;
	toklist = NULL;
	i = 0;
	while (cmd[i] != '\0')
	{
		type = get_char_type(&cmd[i]);
		if (state == STATE_DEFAULT)
		{
			if (type == CHAR_DEFAULT)
				token_str = ft_append_char(token_str, cmd[i]);
			else if (type == CHAR_DQUOTE)
			{
				token_str = ft_append_char(token_str, cmd[i]);
				state = STATE_DQUOTE;
			}
			else if (type == CHAR_QUOTE)
			{
				token_str = ft_append_char(token_str, cmd[i]);
				state = STATE_QUOTE;
			}
			else if (type == CHAR_SPACE)
				add_token(&toklist, &token_str, TOKEN);
			else if (type == CHAR_PIPE)
			{
				add_token(&toklist, &token_str, TOKEN);
				token_str = ft_append_char(token_str, '|');
				add_token(&toklist, &token_str, CHAR_PIPE);
			}
			else if (type == CHAR_OR)
			{
				add_token(&toklist, &token_str, TOKEN);
				// TODO: Create ft_append_str
				token_str = ft_append_char(token_str, '|');
				token_str = ft_append_char(token_str, '|');
				add_token(&toklist, &token_str, CHAR_OR);
				i++;
			}
			else if (type == CHAR_AND)
			{
				add_token(&toklist, &token_str, TOKEN);
				token_str = ft_append_char(token_str, '&');
				token_str = ft_append_char(token_str, '&');
				add_token(&toklist, &token_str, CHAR_AND);
				i++;
			}
			else if (type == CHAR_IN)
			{
				add_token(&toklist, &token_str, TOKEN);
				token_str = ft_append_char(token_str, '<');
				add_token(&toklist, &token_str, CHAR_IN);
			}
			else if (type == CHAR_OUT)
			{
				add_token(&toklist, &token_str, TOKEN);
				token_str = ft_append_char(token_str, '>');
				add_token(&toklist, &token_str, CHAR_OUT);
			}
			else if (type == CHAR_HEREDOC)
			{
				add_token(&toklist, &token_str, TOKEN);
				token_str = ft_append_char(token_str, '<');
				token_str = ft_append_char(token_str, '<');
				add_token(&toklist, &token_str, CHAR_HEREDOC);
				i++;
			}
			else if (type == CHAR_APPEND)
			{
				add_token(&toklist, &token_str, TOKEN);
				token_str = ft_append_char(token_str, '>');
				token_str = ft_append_char(token_str, '>');
				add_token(&toklist, &token_str, CHAR_APPEND);
				i++;
			}
		}
		else
			in_quotes(&state, &token_str, type, cmd[i]);
		++i;
	}
	add_token(&toklist, &token_str, TOKEN);
	return (toklist);
}