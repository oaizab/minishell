/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:18:11 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/14 18:31:24 by hhamza           ###   ########.fr       */
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
	t_ast_node	*ast;

	ft_hide_ctrl_c();
	ft_install_signals();
	while (1)
	{
		cmd = ft_read_cmd();
		toklist = ft_lexer(cmd);
		ast = ft_parser(toklist);
		if (ast == NULL)
		{
			free(cmd);
			continue ;
		}
		display_ast(ast);
		ft_ast_free(ast);
		free(cmd);
	}
	return (0);
}
