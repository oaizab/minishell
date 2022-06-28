/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 14:33:10 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/28 16:12:21 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BUILTIN_H
# define FT_BUILTIN_H

# include "minishell.h"

int		ft_echo(char **args, int fd);
int		ft_cd(char **args, t_env **env, int fd);
int		ft_pwd(int fd);
void	ft_export(char **args, t_ft_env *ft_env, int fd);
void	ft_unset(char **args, t_ft_env *ft_env);
int		ft_env(char **args, t_ft_env *ft_env, int fd);
void	ft_exit(char **args, t_ft_env *ft_env);

int		ft_count_args(char **args);

#endif