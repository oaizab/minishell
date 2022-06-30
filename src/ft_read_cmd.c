/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 09:29:57 by hhamza            #+#    #+#             */
/*   Updated: 2022/06/30 08:56:33 by hhamza           ###   ########.fr       */
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
	prompt = ft_append_str(prompt, " $ \001\e[00m\002");
	return (prompt);
}

/**
 * @brief Putchar function for termcaps
 *
 * @param c: character to put
 * @return int: character put count
 */
static int	ft_termcap_putchar(int c)
{
	return (write(STDOUT_FILENO, &c, 1));
}

/**
 * @brief Print exit using termcaps
 *
 * @param env_s: environment object
 * @param prompt: prompt string
 */
static void	ft_termcap_exit(t_ft_env *env_s, char *prompt)
{
	char	*term;
	char	*sr_cap;

	term = ft_env_get(env_s->env, "TERM");
	if (term == NULL)
	{
		ft_printf("exit\n");
		return ;
	}
	tgetent(NULL, term);
	sr_cap = tgetstr("sr", NULL);
	tputs(sr_cap, 0, &ft_termcap_putchar);
	ft_printf("%sexit\n", prompt);
	free(prompt);
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
	if (cmd == NULL)
	{
		ft_termcap_exit(env_s, prompt);
		ft_restore_ctrl_c();
		rl_clear_history();
		ft_env_clear(&env_s->env);
		ft_env_clear(&env_s->export);
		exit(g_exit_status);
	}
	if (ft_strlen(cmd) == 0)
	{
		free(cmd);
		return (ft_read_cmd(env_s));
	}
	add_history(cmd);
	return (cmd);
}
