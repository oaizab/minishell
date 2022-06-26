/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 09:29:57 by hhamza            #+#    #+#             */
/*   Updated: 2022/06/26 12:05:46 by oaizab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_get_prompt(void)
{
	char	*prompt;
	char	*path;
	char	*basename;

	prompt = ft_strdup("\001\e[01;32m\002");
	path = getcwd(NULL, 0);
	basename = ft_strrchr(path, '/');
	if (basename)
		basename++;
	else
		basename = path;
	if (*basename == '\0')
		basename = ft_strdup("/");
	else
		basename = ft_strdup(basename);
	free(path);
	prompt = ft_append_str(prompt, basename);
	free(basename);
	prompt = ft_append_str(prompt, "\001\e[00m\002 $ ");
	return (prompt);
}

/**
 * @brief Read command from standard input
 * @note This function exits if Ctrl-D or "exit" is provided as a command
 *
 * @return char*: Command string
 */
char	*ft_read_cmd(void)
{
	char	*cmd;
	char	*prompt;

	prompt = ft_get_prompt();
	cmd = readline(prompt);
	free(prompt);
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
