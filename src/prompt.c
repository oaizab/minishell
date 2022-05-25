/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:13:14 by oaizab            #+#    #+#             */
/*   Updated: 2022/05/25 15:42:23 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_cmd(void)
{
	char	*cmd;

	cmd = readline("minishell $ ");
	if (!cmd)
		ft_exit(EXIT_SUCCESS);
	if (!ft_strlen(cmd))
		return (free(cmd), read_cmd());
	add_history(cmd);
	if (!strcmp(cmd, "exit"))
		(free(cmd), ft_exit(EXIT_SUCCESS));
	return (cmd);
}
