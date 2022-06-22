/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 11:43:47 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/22 18:49:48 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXPANDER_H
# define FT_EXPANDER_H

void	ft_expander(t_ast_node *node, t_env *env);
bool	ft_heredoc_expander(t_ast_node *node, t_env *env);

#endif