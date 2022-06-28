/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 13:44:00 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/28 18:35:42 by oaizab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXECUTOR_H
# define FT_EXECUTOR_H

void	ft_executor(t_ast_node *root, t_ft_env *env);
bool	ft_execute_redir(t_ast_node *node);
void	ft_execute_cmd(t_ast_node *node, t_ft_env *env);

bool	ft_is_builtin(char *cmd);
bool	ft_execute_builtin(t_ast_node *root, t_ft_env *ft_env);
bool	ft_expand_command(t_ast_node *root, t_env *env);
void	ft_execute_cmd_fork(t_ast_node *node, t_ft_env *env);
void	ft_underscore(t_ast_node *node, t_ft_env *env);
void	ft_redir_error(char *name);

#endif