/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 09:46:17 by hhamza            #+#    #+#             */
/*   Updated: 2022/06/28 10:01:05 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Print environment.
 *
 * @param args: Arguments array
 * @param ft_env: Environment object
 * @param fd: File descriptor to write to
 * @return int: 0 on success, 1 on failure
 */
int	ft_env(char **args, t_ft_env *ft_env, int fd)
{
	int		argc;
	char	**print_env;
	int		i;

	argc = ft_count_args(args);
	if (argc != 1)
	{
		ft_fprintf(STDERR_FILENO, "minishell: env: too many arguments\n");
		return (1);
	}
	print_env = ft_env_to_array(ft_env->env);
	if (print_env == NULL)
	{
		ft_error(ERR_MALLOC, NULL);
		return (1);
	}
	i = 0;
	while (print_env[i] != NULL)
	{
		ft_fprintf(fd, "%s\n", print_env[i]);
		++i;
	}
	return (0);
}
