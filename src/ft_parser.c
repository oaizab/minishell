/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 16:20:43 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/16 14:15:44 by oaizab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Minishell parser.
 *
 * @param toklist: Token list to parse
 * @return t_ast_node*: Abstract syntax tree, NULL on failure
 */
t_ast_node	*ft_parser(char *cmd)
{
	t_toklist	*toklist;
	t_scanner	*scanner;
	t_ast_node	*ast;

	toklist = ft_lexer(cmd);
	free(cmd);
	if (!toklist)
		return (NULL);
	scanner = ft_scanner_new(toklist);
	if (scanner == NULL)
		return (NULL);
	if (ft_scanner_peek(scanner)->type == TOKEN_END)
		return (NULL);
	ast = ft_parse_cmdline(scanner);
	if (ast == NULL)
	{
		ft_scanner_destroy(&scanner);
		return (NULL);
	}
	ft_scanner_destroy(&scanner);
	return (ast);
}
