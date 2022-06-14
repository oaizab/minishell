/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 16:20:06 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/14 14:33:29 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSER_H
# define FT_PARSER_H

# include "ft_ast.h"

t_ast_node	*ft_parse_redir(t_scanner *scanner);
bool		ft_is_redir(t_token_type type);
t_ast_node	*ft_parse_cmdlist(t_scanner *t_scanner);
bool		ft_is_cmdlist(t_token_type type);
t_ast_node	*ft_parse_command(t_scanner *scanner);
bool		ft_is_command(t_token_type type);
t_ast_node	*ft_parse_pipeline(t_scanner *scanner);
t_ast_node	*ft_parse_block(t_scanner *scanner);
t_ast_node	*ft_parse_cmdline(t_scanner *scanner);

#endif