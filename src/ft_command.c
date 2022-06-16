/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:05:08 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/16 14:52:44 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Parse a subshell
 *
 * @param scanner: Scanner object.
 * @param lvl: Parenthesis depth level.
 * @return t_ast_node*: Subshell node, NULL on failure.
 */
static t_ast_node	*ft_parse_subshell(t_scanner *scanner, int *lvl)
{
	t_ast_node	*subshell;

	get_next_token(scanner);
	if (ft_is_command(ft_scanner_peek(scanner)->type))
		subshell = ft_parse_cmdline(scanner);
	else
	{
		*lvl = 0;
		return (ft_error(ERR_SYNTAX, ft_scanner_peek(scanner)), NULL);
	}
	if (subshell == NULL)
	{
		*lvl = 0;
		return (NULL);
	}
	if (ft_scanner_peek(scanner)->type != TOKEN_CPAR)
	{
		*lvl = 0;
		return (ft_ast_free(subshell), ft_error(ERR_CPAR, NULL), NULL);
	}
	get_next_token(scanner);
	(*lvl)--;
	return (subshell);
}

static bool	ft_parse_command_helper(t_ast_node **subshell, t_scanner *scanner, \
	int lvl)
{
	*subshell = ft_parse_cmdlist(scanner);
	if (*subshell == NULL)
		return (false);
	if (lvl == 0 && !ft_is_binary(ft_scanner_peek(scanner)->type))
		return (ft_ast_free(*subshell), \
			ft_error(ERR_SYNTAX, ft_scanner_peek(scanner)), false);
	return (true);
}

/**
 * @brief Parse a command
 *
 * @param scanner: Scanner object.
 * @return t_ast_node*: Command node, NULL on failure.
 */
t_ast_node	*ft_parse_command(t_scanner *scanner)
{
	t_ast_node	*subshell;
	static int	lvl = 0;

	if (ft_is_cmdlist(ft_scanner_peek(scanner)->type))
	{
		if (ft_parse_command_helper(&subshell, scanner, lvl) == true)
			return (subshell);
		else
			return (NULL);
	}
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
	return (NULL);
}
