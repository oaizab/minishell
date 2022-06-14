/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:13:14 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/02 10:23:23 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Read command from standard input
 * @note This function exits if Ctrl-D or "exit" is provided as a command
 *
 * @return char*: Command string
 */
char	*ft_read_cmd(void)
{
	char	*cmd;

	cmd = readline("minishell $ ");
	if (cmd == NULL)
	{
		ft_exit(EXIT_SUCCESS);
	}
	if (ft_strlen(cmd) == 0)
	{
		free(cmd);
		return (ft_read_cmd());
	}
	add_history(cmd);
	if (strcmp(cmd, "exit") == 0)
	{
		free(cmd);
		ft_exit(EXIT_SUCCESS);
	}
	return (cmd);
}
