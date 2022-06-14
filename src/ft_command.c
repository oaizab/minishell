/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:05:08 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/14 15:19:37 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_is_command(t_token_type type)
{
	return (ft_is_cmdlist(type) || type == TOKEN_OPAR);
}

static bool	ft_is_binary(t_token_type type)
{
	return (type == TOKEN_OR || type == TOKEN_AND || type == TOKEN_PIPE \
		|| type == TOKEN_END);
}

static bool	ft_is_closed(t_token_type type)
{
	return (type == TOKEN_CPAR || ft_is_binary(type));
}

static t_ast_node	*ft_parse_subshell(t_scanner *scanner, int *lvl)
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
	{
		*lvl = 0;
		return (ft_ast_free(subshell), ft_error(ERR_CPAR, NULL), NULL);
	}
	get_next_token(scanner);
	(*lvl)--;
	return (subshell);
}

t_ast_node	*ft_parse_command(t_scanner *scanner)
{
	t_ast_node	*subshell;
	static int	lvl = 0;

	if (ft_is_cmdlist(ft_scanner_peek(scanner)->type))
		return (ft_parse_cmdlist(scanner));
	else if (ft_scanner_peek(scanner)->type == TOKEN_OPAR)
	{
		lvl++;
		subshell = ft_parse_subshell(scanner, &lvl);
		if (subshell == NULL)
			return (NULL);
		if (lvl > 0 && !ft_is_closed(ft_scanner_peek(scanner)->type))
			return (ft_ast_free(subshell), ft_error(ERR_SYNTAX, \
				ft_scanner_peek(scanner)), NULL);
		if (lvl == 0 && !ft_is_binary(ft_scanner_peek(scanner)->type))
			return (ft_ast_free(subshell), \
				ft_error(ERR_SYNTAX, ft_scanner_peek(scanner)), NULL);
		return (subshell);
	}
	else
		return (NULL);
}
