/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 16:50:18 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/13 16:51:28 by oaizab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node *ft_parse_cmdline(t_scanner *scanner)
{
	if (!ft_is_command(ft_scanner_peek(scanner)->type))
		return (ft_error(ERR_SYNTAX, ft_scanner_peek(scanner)), NULL);
	return (ft_parse_block(scanner));
}
