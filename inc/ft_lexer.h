/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 09:24:04 by hhamza            #+#    #+#             */
/*   Updated: 2022/06/15 11:38:28 by oaizab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LEXER_H
# define FT_LEXER_H

# include "libft.h"
# include <stdbool.h>

/**
 * @brief Minishell lexer API.
 *
 * @datatypes:
 *  * t_token_type: Token types enumeration.
 *  * t_state: Lexer states enumeration.
 *  * t_token: Token structure.
 *  * t_toklist: Token list structure.
 *
 * @features:
 *  * ft_token_init: Initialize a token.
 *  * ft_token_destroy: Destroy a token.
 *  * ft_add_token: Add a token to a token list.
 *  * ft_get_token_type: Get token type.
 *  * ft_lexer: Minishell lexer.
 */

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_IN,
	TOKEN_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
	TOKEN_QUOTE,
	TOKEN_DQUOTE,
	TOKEN_SPACE,
	TOKEN_OPAR,
	TOKEN_CPAR,
	TOKEN_END
}			t_token_type;

typedef enum e_state
{
	STATE_QUOTE,
	STATE_DQUOTE,
	STATE_DEFAULT
}			t_state;

typedef struct s_token {
	char			*lexeme;
	t_token_type	type;
}			t_token;

typedef t_list	t_toklist;

t_token			*ft_token_init(char *lexeme, t_token_type type);
void			ft_token_destroy(void *tok_addr);
bool			ft_add_token(t_toklist **toklist, char **token_str, \
	t_token_type type);
t_token_type	ft_get_token_type(const char *lexeme);
t_toklist		*ft_lexer(const char *cmd);

void			ft_token_end(t_toklist **toklist);
bool			ft_default_state(t_toklist **toklist, t_token_type type, \
	char **token_str, int *i);

#endif