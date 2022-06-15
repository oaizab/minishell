/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 16:20:06 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/15 09:22:58 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSER_H
# define FT_PARSER_H

# include "ft_ast.h"

/**
 * @brief Minishell parser API.
 *
 * @features:
 *  * ft_parse_redir: Parse redirection.
 *  * ft_parse_cmdlist: Parse command list.
 *  * ft_parse_command: Parse command.
 *  * ft_parse_pipeline: Parse pipeline.
 *  * ft_parse_block: Parse block.
 *  * ft_parse_cmdline: Parse command line.
 *  * ft_parser: Minishell parser.
 */

t_ast_node	*ft_parse_redir(t_scanner *scanner);
t_ast_node	*ft_parse_cmdlist(t_scanner *t_scanner);
t_ast_node	*ft_parse_command(t_scanner *scanner);
t_ast_node	*ft_parse_pipeline(t_scanner *scanner);
t_ast_node	*ft_parse_block(t_scanner *scanner);
t_ast_node	*ft_parse_cmdline(t_scanner *scanner);
t_ast_node	*ft_parser(t_toklist *toklist);

bool		ft_is_redir(t_token_type type);
bool		ft_is_cmdlist(t_token_type type);
bool		ft_is_command(t_token_type type);

#endif