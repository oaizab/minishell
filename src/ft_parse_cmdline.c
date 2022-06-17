/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_cmdline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:25:36 by hhamza            #+#    #+#             */
/*   Updated: 2022/06/17 15:25:37 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Parse a command line.
 *
 * @param scanner: Scanner object.
 * @return t_ast_node*: Command line node, NULL on failure.
 */
t_ast_node	*ft_parse_cmdline(t_scanner *scanner)
{
	if (!ft_is_command(ft_scanner_peek(scanner)->type))
		return (ft_error(ERR_SYNTAX, ft_scanner_peek(scanner)), NULL);
	return (ft_parse_block(scanner));
}
