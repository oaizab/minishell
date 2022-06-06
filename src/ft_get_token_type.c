/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_token_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 11:19:18 by hhamza            #+#    #+#             */
/*   Updated: 2022/06/02 11:43:15 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Helper function for ft_get_token_type for norm reasons
 *
 * @param lexeme: Token lexeme (Token string)
 * @return t_token_type: Token type
 */
static t_token_type	ft_get_token_type_helper(const char *lexeme)
{
	if (ft_strncmp(lexeme, "<<", 2) == 0)
		return (TOKEN_HEREDOC);
	else if (ft_strncmp(lexeme, "<", 1) == 0)
		return (TOKEN_IN);
	else if (ft_strncmp(lexeme, ">>", 2) == 0)
		return (TOKEN_APPEND);
	else if (ft_strncmp(lexeme, ">", 1) == 0)
		return (TOKEN_OUT);
	else
		return (TOKEN_DEFAULT);
}

/**
 * @brief Get token type
 *
 * @param lexeme: Token lexeme (Token string)
 * @return t_token_type: Token type or -1 if token is invalid
 */
t_token_type	ft_get_token_type(const char *lexeme)
{
	if (lexeme == NULL || lexeme[0] == '\0')
		return (-1);
	else if (ft_strncmp(lexeme, "&&", 2) == 0)
		return (TOKEN_AND);
	else if (ft_strncmp(lexeme, "||", 2) == 0)
		return (TOKEN_OR);
	else if (ft_strncmp(lexeme, "|", 1) == 0)
		return (TOKEN_PIPE);
	else if (ft_strncmp(lexeme, "'", 1) == 0)
		return (TOKEN_QUOTE);
	else if (ft_strncmp(lexeme, "\"", 1) == 0)
		return (TOKEN_DQUOTE);
	else if (ft_strncmp(lexeme, " ", 1) == 0)
		return (TOKEN_SPACE);
	else if (ft_strncmp(lexeme, "(", 1) == 0)
		return (TOKEN_OPAR);
	else if (ft_strncmp(lexeme, ")", 1) == 0)
		return (TOKEN_CPAR);
	else
		return (ft_get_token_type_helper(lexeme));
}
