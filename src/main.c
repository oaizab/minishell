/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:18:11 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/02 10:22:25 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Print token list
 *
 * @param toklist: Token list
 */
static void	ft_print_toklist(t_toklist *toklist)
{
	t_token	*tokptr;

	while (toklist != NULL)
	{
		tokptr = toklist->content;
		printf("[%s] ", tokptr->tok);
		toklist = toklist->next;
	}
	printf("\n");
}

int	main(void)
{
	char		*cmd;
	t_toklist	*toklist;

	ft_hide_ctrl_c();
	ft_install_signals();
	while (1)
	{
		cmd = ft_read_cmd();
		toklist = ft_lexer(cmd);
		ft_print_toklist(toklist);
		free(cmd);
	}
	return (0);
}
