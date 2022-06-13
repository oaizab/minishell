/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:05:08 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/13 17:13:54 by oaizab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_is_command(t_token_type type)
{
	return (ft_is_cmdlist(type) || type == TOKEN_OPAR);
}

static bool	ft_is_binary(t_token_type type)
{
	return (type == TOKEN_OR || type == TOKEN_AND || type == TOKEN_PIPE);
}

static t_ast_node	*ft_parse_subshell(t_scanner *scanner)
{
	t_ast_node	*subshell;

	get_next_token(scanner);
	if (ft_is_command(ft_scanner_peek(scanner)->type))
		subshell = ft_parse_cmdline(scanner);
	else
		return (ft_error(ERR_SYNTAX, ft_scanner_peek(scanner)), NULL);
	if (subshell == NULL)
		return (NULL);
	if (ft_scanner_peek(scanner)->type != TOKEN_CPAR)
		return (ft_error(ERR_CPAR, NULL), NULL);
	get_next_token(scanner);
	return (subshell);
}

t_ast_node	*ft_parse_command(t_scanner *scanner)
{
	t_ast_node	*subshell;

	if (ft_is_cmdlist(ft_scanner_peek(scanner)->type))
		return (ft_parse_cmdlist(scanner));
	else if (ft_scanner_peek(scanner)->type == TOKEN_OPAR)
	{
		subshell = ft_parse_subshell(scanner);
		if (!ft_is_binary(ft_scanner_peek(scanner)->type))
			return (ft_error(ERR_SYNTAX, ft_scanner_peek(scanner)), NULL);
		return (subshell);
	}
	else
		return (NULL);
}
