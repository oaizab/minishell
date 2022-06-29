/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 09:29:57 by hhamza            #+#    #+#             */
/*   Updated: 2022/06/29 11:50:09 by oaizab           ###   ########.fr       */
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
 * @brief Read command from standard input
 * @note This function exits if Ctrl-D or "exit" is provided as a command
 *
 * @return char*: Command string
 */
char	*ft_read_cmd(t_ft_env *env_s)
{
	char	*cmd;
	char	*prompt;
	int		prompt_len;

	prompt = ft_get_prompt(env_s->env);
	cmd = readline(prompt);
	prompt_len = ft_strlen(prompt);
	free(prompt);
	if (cmd == NULL)
	{
		ft_printf("\033[1A\033[%dCexit\n", prompt_len - 17);
		ft_restore_ctrl_c();
		rl_clear_history();
		ft_env_clear(&env_s->env);
		ft_env_clear(&env_s->export);
		exit(g_exit_status);
	}
	if (ft_strlen(cmd) == 0)
	{
		free(cmd);
		free(prompt);
		return (ft_read_cmd(env_s));
	}
	add_history(cmd);
	return (cmd);
}
