/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:13:14 by oaizab            #+#    #+#             */
/*   Updated: 2022/05/19 17:47:41 by oaizab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_cmd(void)
{
	char	*cmd;

	cmd = readline("minishell $ ");
	if (!cmd)
		exit(EXIT_SUCCESS);
	if (!ft_strlen(cmd))
		return (free(cmd), read_cmd());
	add_history(cmd);
	if (!strcmp(cmd, "exit"))
		(free(cmd), exit(EXIT_SUCCESS));
	return (cmd);
}
