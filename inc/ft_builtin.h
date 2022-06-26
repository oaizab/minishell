/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 14:33:10 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/26 09:37:43 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BUILTIN_H
# define FT_BUILTIN_H

# include "minishell.h"

int	ft_echo(char **args, int fd);
int	ft_cd(char **args, t_env **env);
int	ft_pwd(int fd);

int	ft_count_args(char **args);

#endif