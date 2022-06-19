/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 18:20:22 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/19 08:33:28 by oaizab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Print syntax error message.
 *
 * @param token: Token object where the error occured.
 */
static void	ft_syntax_error(t_token *token)
{
	ft_fprintf(2, "minishell: syntax error near unexpected token '%s'\n", \
		token->lexeme);
}

/**
 * @brief Print error message.
 *
 * @param err: Error type.
 * @param token: Token object where the error occured.
 */
void	ft_error(t_error err, t_token *token)
{
	g_exit_status = 258;
	if (err == ERR_MALLOC)
		ft_putendl_fd("Error: malloc failed", 2);
	else if (err == ERR_SYNTAX)
		ft_syntax_error(token);
	else if (err == ERR_CPAR)
		ft_fprintf(2, "minishell: syntax error unclosed parenthesis\n");
	else if (err == ERR_QUOTE)
		ft_fprintf(2, "minishell: syntax error unclosed quote\n");
}
