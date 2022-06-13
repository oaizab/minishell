/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 18:20:22 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/13 17:06:41 by oaizab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_syntax_error(t_token *token)
{
	ft_fprintf(2, "minishell: syntax error near unexpected token '%s'\n", token->lexeme);
}

void ft_error(t_error err, t_token *token)
{
	if (err == ERR_MALLOC)
	{
		ft_putendl_fd("Error: malloc failed", 2);
	}
	else if (err == ERR_SYNTAX)
		ft_syntax_error(token);
	else if (err == ERR_CPAR)
		ft_fprintf(2, "minishell: syntax error unclosed parenthesis\n");
}
