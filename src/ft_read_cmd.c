/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 09:29:57 by hhamza            #+#    #+#             */
/*   Updated: 2022/06/29 10:58:49 by oaizab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_prompt(t_env *env)
{
	char	*prompt;
	char	*path;
	char	*basename;

	prompt = ft_strdup("\001\e[01;32m\002");
	path = ft_env_get(env, "PWD");
	if (path == NULL)
		path = "/[no-dir]";
	basename = ft_strrchr(path, '/');
	if (basename)
		basename++;
	else
		basename = path;
	if (*basename == '\0')
		basename = ft_strdup("/");
	else
		basename = ft_strdup(basename);
	prompt = ft_append_str(prompt, basename);
	free(basename);
	prompt = ft_append_str(prompt, "\001\e[00m\002 $ ");
	return (prompt);
}

/**
 * @brief Print exit when receiving Ctrl-D
 *
 * @param prompt: prompt string
 */
static void	ft_ctrl_d_exit(char *prompt)
{
	int	len;

	len = ft_strlen(prompt);
	ft_printf("\033[1A\033[%dCexit\n", len - 17);
	free(prompt);
}

/**
 * @brief Read command from standard input
 * @note This function exits if Ctrl-D or "exit" is provided as a command
 *
 * @return char*: Command string
 */
char	*ft_read_cmd(t_env *env)
{
	char	*cmd;
	char	*prompt;

	prompt = ft_get_prompt(env);
	cmd = readline(prompt);
	if (cmd == NULL)
	{
		ft_ctrl_d_exit(prompt);
		ft_restore_ctrl_c();
		rl_clear_history();
		exit(g_exit_status);
	}
	if (ft_strlen(cmd) == 0)
	{
		free(cmd);
		return (ft_read_cmd(env));
	}
	add_history(cmd);
	return (cmd);
}
