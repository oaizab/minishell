/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:18:11 by oaizab            #+#    #+#             */
/*   Updated: 2022/05/24 17:58:59 by oaizab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char		*cmd;
	t_toklist	*toklist;
	t_token		*tokptr;

	while (1)
	{
		cmd = read_cmd();
		toklist = ft_lexer(cmd);
		// printf("%p\n", toklist);
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
