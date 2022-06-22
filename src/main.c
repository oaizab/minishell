/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:18:11 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/22 13:34:40 by oaizab           ###   ########.fr       */
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

int	main(int argc, char **argv, char **env)
{
	char		*cmd;
	t_ast_node	*ast;
	t_env		*env_list;

	env_list = ft_env_init(env);
	(void) argc, (void) argv;
	ft_env_add(&env_list, "A", "a   b       c");
	ft_hide_ctrl_c();
	ft_install_signals();
	while (1)
	{
		cmd = ft_read_cmd();
		ast = ft_parser(cmd);
		if (ast == NULL)
			continue ;
		ft_executor(ast, env_list, env_list);
		display_ast(ast);
		ft_ast_free(ast);
	}
	return (0);
}
