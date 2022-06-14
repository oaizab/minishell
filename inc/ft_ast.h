/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 09:31:33 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/14 09:30:29 by oaizab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_AST_H
# define FT_AST_H

# define ARG_MAX 262144

# include "minishell.h"

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
	t_node_type			type;
	char				*value;
	char				**args;
	t_redir_type		redir_type;
	struct s_ast_node		*left;
	struct s_ast_node		*right;
}				t_ast_node;

t_ast_node	*ft_ast_node_new(t_node_type type, char *value);
void		ft_insert_child(t_ast_node *root, t_ast_node *left, \
	t_ast_node *right);
void		display_ast(t_ast_node *root);
void		ft_ast_free(t_ast_node *root);

#endif