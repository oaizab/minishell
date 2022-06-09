/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 09:24:04 by hhamza            #+#    #+#             */
/*   Updated: 2022/06/09 16:10:14 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LEXER_H
# define FT_LEXER_H

# include "libft.h"

typedef enum e_token_type
{
	TOKEN_DEFAULT,
	TOKEN,
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
void			ft_add_token(t_toklist **toklist, char **token_str, \
	t_token_type type);

t_token_type	ft_get_token_type(const char *lexeme);
void			ft_token_end(t_toklist **toklist);
t_toklist		*ft_lexer(const char *cmd);

#endif