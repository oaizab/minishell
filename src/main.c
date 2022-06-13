/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:18:11 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/13 16:51:48 by oaizab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Print token list
 *
 * @param toklist: Token list
 */
void	ft_print_toklist(t_toklist *toklist)
{
	t_token	*tokptr;

	while (toklist != NULL)
	{
		tokptr = toklist->content;
		printf("[%s] ", tokptr->lexeme);
		toklist = toklist->next;
	}
	printf("\n");
}

int	main(void)
{
	char		*cmd;
	t_toklist	*toklist;
	t_scanner	*scanner;
	t_ast_node	*ast;

	ft_hide_ctrl_c();
	ft_install_signals();
	while (1)
	{
		cmd = ft_read_cmd();
		toklist = ft_lexer(cmd);
		scanner = ft_scanner_new(toklist);
		if ((ast = ft_parse_cmdline(scanner)) == NULL)
		{
			ft_scanner_destroy(&scanner);
			free(cmd);
			continue;
		}
		display_ast(ast);
		// ft_print_toklist(toklist);
		// ft_lstclear(&toklist, &ft_token_destroy);
		free(cmd);
	}
	return (0);
}
