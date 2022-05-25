/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:18:11 by oaizab            #+#    #+#             */
/*   Updated: 2022/05/25 15:42:47 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char		*cmd;
	t_toklist	*toklist;
	t_token		*tokptr;

	hide_ctrl_c();
	install_signals();
	while (1)
	{
		cmd = read_cmd();
		toklist = ft_lexer(cmd);
		while (toklist != NULL)
		{
			tokptr = toklist->content;
			printf("[%s] ", tokptr->tok);
			toklist = toklist->next;
		}
		printf("\n");
		free(cmd);
	}
	return (0);
}
