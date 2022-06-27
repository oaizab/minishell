/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 13:44:00 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/27 19:25:29 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXECUTOR_H
# define FT_EXECUTOR_H

void	ft_executor(t_ast_node *root, t_ft_env *env);
bool	ft_execute_redir(t_ast_node *node);
void	ft_execute_cmd(t_ast_node *node, t_env *env);

bool	ft_is_builtin(char *cmd);
void	ft_execute_builtin(t_ast_node *root, t_ft_env *ft_env);

#endif