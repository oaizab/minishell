/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 10:04:16 by hhamza            #+#    #+#             */
/*   Updated: 2022/06/30 07:12:47 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

void	ft_exit(char **args, t_ft_env *ft_env)
{
	int	argc;
	int	status;

	ft_env_clear(&ft_env->env);
	ft_env_clear(&ft_env->export);
	ft_restore_ctrl_c();
	rl_clear_history();
	ft_printf("exit\n");
	argc = ft_count_args(args);
	if (argc == 1)
	{
		exit(g_exit_status);
	}
	else
	{
		status = ft_atoi(args[1]);
		exit(status);
	}
}
