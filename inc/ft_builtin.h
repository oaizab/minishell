/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 14:33:10 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/28 20:10:00 by oaizab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BUILTIN_H
# define FT_BUILTIN_H

# include "minishell.h"

int		ft_echo(char **args, int fd);
int		ft_cd(char **args, t_env **env, int fd);
int		ft_pwd(int fd, t_env *env);
void	ft_export(char **args, t_ft_env *ft_env, int fd);
void	ft_unset(char **args, t_ft_env *ft_env);
int		ft_env(char **args, t_ft_env *ft_env, int fd);
void	ft_exit(char **args, t_ft_env *ft_env);

int		ft_count_args(char **args);

#endif