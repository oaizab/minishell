/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 10:28:04 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/27 14:35:50 by oaizab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_redir_error(char *name)
{
	ft_fprintf(2, "minishell: %s: No such file or directory\n", name);
	g_exit_status = 1;
}

bool	ft_redir_in(t_ast_node *node, char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY, 0644);
	if (fd == -1)
		return (false);
	if (node->in != STDIN_FILENO)
		close(node->in);
	node->in = fd;
	return (true);
}

bool	ft_redir_out(t_ast_node *node, char *filename, t_redir_type type)
{
	int fd;

	if (type == REDIR_OUT)
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		return (false);
	if (node->out != STDOUT_FILENO)
		close(node->out);
	node->out = fd;
	return (true);
}

bool	ft_execute_redir(t_ast_node *node)
{
	t_ast_node	*tmp;

	tmp = node;
	while (tmp->left)
	{
		tmp = tmp->left;
		if (tmp->args[1] != NULL)
			return (false);
		if (tmp->redir_type == REDIR_IN)
		{
			if (!ft_redir_in(node, tmp->value))
				return (ft_redir_error(tmp->value), false);
		}
		else if (tmp->redir_type == REDIR_OUT)
		{
			if (!ft_redir_out(node, tmp->value, REDIR_OUT))
				return (ft_redir_error(tmp->value), false);
		}
		else if (tmp->redir_type == REDIR_APPEND)
		{
			if (!ft_redir_out(node, tmp->value, REDIR_APPEND))
				return (ft_redir_error(tmp->value), false);
		}
	}
	return (true);
}
