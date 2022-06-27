/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 07:36:37 by hhamza            #+#    #+#             */
/*   Updated: 2022/06/27 21:08:27 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Change current working directory to home directory (Helper function
 * for ft_cd).
 *
 * @param env: Environment object
 * @return int: 0 if success, 1 on failure
 */
static int	ft_cd_home(t_env **env)
{
	char	*home;
	char	*oldpwd;

	home = ft_env_get(*env, "HOME");
	if (home == NULL)
		return (ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO), 1);
	else
	{
		oldpwd = getcwd(NULL, 0);
		if (oldpwd == NULL)
		{
			return (ft_error(ERR_MALLOC, NULL), 1);
		}
		if (chdir(home) == -1)
		{
			ft_fprintf(STDERR_FILENO, \
				"minishell: cd: %s: No such file or directory\n", home);
			free(oldpwd);
			return (1);
		}
		ft_env_add(env, "OLDPWD", oldpwd);
		ft_env_add(env, "PWD", home);
		free(oldpwd);
		return (0);
	}
}

/**
 * @brief Change current working directory to specifed path (Helper
 * function for ft_cd).
 *
 * @param path: Path to change to
 * @param env: Environment object
 * @return int: 0 if success, 1 on failure
 * @note: Replaced STDERR_FILENO by 2 for norm reasons.
 */
static int	ft_cd_path(char *path, t_env **env)
{
	char	*oldpwd;
	char	*pwd;

	oldpwd = getcwd(NULL, 0);
	if (oldpwd == NULL)
	{
		ft_error(ERR_MALLOC, NULL);
		return (1);
	}
	if (chdir(path) == -1)
	{
		ft_fprintf(STDERR_FILENO, "minishell: cd: %s: ", path);
		return (perror(NULL), free(oldpwd), 1);
	}
	ft_env_add(env, "OLDPWD", oldpwd);
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		return (ft_error(ERR_MALLOC, NULL), free(oldpwd), 1);
	}
	ft_env_add(env, "PWD", pwd);
	free(oldpwd);
	free(pwd);
	return (0);
}

/**
 * @brief Change current wotking directory to last visired directory (Helper
 * function for ft_cd).
 *
 * @param env: Environment object
 * @param fd: File descriptor to write to
 * @return int: 0 if success, 1 on failure
 */
static int	ft_cd_dash(t_env **env, int fd)
{
	char	*tmp;

	tmp = ft_env_get(*env, "OLDPWD");
	if (ft_strcmp(tmp, "") == 0)
	{
		ft_putendl_fd("minishell: cd: OLDPWD not set", STDERR_FILENO);
		return (1);
	}
	else
	{
		ft_fprintf(fd, "%s\n", tmp);
		return (ft_cd_path(tmp, env));
	}
}

/**
 * @brief Change current working directory (minishell builtin).
 *
 * @param args: Arguments array
 * @param env: Environment object
 * @param fd: File descriptor to write to
 * @return int: 0 if success, 1 on failure
 */
int	ft_cd(char **args, t_env **env, int fd)
{
	int		argc;

	argc = ft_count_args(args);
	if (argc == 1)
	{
		return (ft_cd_home(env));
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		return (ft_cd_dash(env, fd));
	}
	else
	{
		return (ft_cd_path(args[1], env));
	}
}
