/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 16:20:43 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/14 18:29:02 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Minishell parser.
 *
 * @param toklist: Token list to parse
 * @return t_ast_node*: Abstract syntax tree, NULL on failure
 */
t_ast_node	*ft_parser(t_toklist *toklist)
{
	t_scanner	*scanner;
	t_ast_node	*ast;

	scanner = ft_scanner_new(toklist);
	if (scanner == NULL)
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
