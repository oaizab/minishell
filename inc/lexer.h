/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:16:39 by oaizab            #+#    #+#             */
/*   Updated: 2022/05/24 17:56:46 by oaizab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"

typedef enum e_char_type
{
	CHAR_DEFAULT = -1,
	TOKEN = -1,
	CHAR_PIPE = '|',
	CHAR_AND = -2,
	CHAR_OR = -3,
	CHAR_IN = '<',
	CHAR_OUT = '>',
	CHAR_HEREDOC = -4,
	CHAR_APPEND = -5,
	CHAR_QUOTE = '\'',
	CHAR_DQUOTE = '"',
	CHAR_SPACE = ' '
}			t_char_type;

typedef enum e_state
{
	STATE_QUOTE,
	STATE_DQUOTE,
	STATE_DEFAULT,
}			t_state;

typedef struct s_token {
	char		*tok;
	t_char_type	type;
}			t_token;

typedef t_list	t_toklist;

t_char_type	get_char_type(const char *c);
t_toklist	*ft_lexer(const char *cmd);

#endif