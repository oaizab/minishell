/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 09:31:33 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/15 08:21:13 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_AST_H
# define FT_AST_H

# include "minishell.h"

/**
 * @brief AST (Abstract Syntax Tree) structure.
 *
 * @datatypes:
 *  * t_node_type: Different node types.
 *  * t_redir_type: Different redirections types.
 *  * t_ast_node: Main AST structure.
 *
 * @features:
 *  * ft_ast_node_new: Create a new AST node.
 *  * display_ast: Display the AST.
 *  * ft_ast_free: Free the AST.
 *
 * @macros:
 *  * ARG_MAX: Maximum number of arguments, this number can be retreived by the
 *  	* following command "getconf ARG_MAX"
 */

# define ARG_MAX 262144

typedef enum e_node_type
{
	NODE_CMD,
	NODE_REDIR,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_HEREDOC,
	NODE_NOCMD
}				t_node_type;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}				t_redir_type;

typedef struct s_ast_node
{
	t_node_type				type;
	char					*value;
	char					**args;
	t_redir_type			redir_type;
	struct s_ast_node		*left;
	struct s_ast_node		*right;
}				t_ast_node;

t_ast_node	*ft_ast_node_new(t_node_type type, char *value);
void		display_ast(t_ast_node *root);
void		ft_ast_free(t_ast_node *root);

#endif