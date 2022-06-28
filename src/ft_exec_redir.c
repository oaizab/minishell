/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 10:28:04 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/28 18:35:55 by oaizab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_redir_heredoc(t_ast_node *node, char *text)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
	{
		ft_fprintf(2, "minishell: pipe: %s\n", strerror(errno));
		return (false);
	}
	node->in = pipefd[0];
	ft_fprintf(pipefd[1], "%s", text);
	close(pipefd[1]);
	return (true);
}

static bool	ft_redir_in(t_ast_node *node, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY, 0644);
	if (fd == -1)
		return (false);
	if (node->in != STDIN_FILENO)
		close(node->in);
	node->in = fd;
	return (true);
}

static bool	ft_redir_out(t_ast_node *node, char *filename, t_redir_type type)
{
	int	fd;

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

static bool	ft_exec_redir_helper(t_ast_node *node, t_ast_node	*tmp)
{
	if (tmp->redir_type == REDIR_OUT)
	{
		if (!ft_redir_out(node, tmp->value, REDIR_OUT))
			return (ft_redir_error(tmp->value), false);
	}
	else if (tmp->redir_type == REDIR_APPEND)
	{
		if (!ft_redir_out(node, tmp->value, REDIR_APPEND))
			return (ft_redir_error(tmp->value), false);
	}
	else if (tmp->redir_type == REDIR_HEREDOC)
	{
		if (!ft_redir_heredoc(node, tmp->value))
			return (false);
	}
	return (true);
}

bool	ft_execute_redir(t_ast_node *node)
{
	t_ast_node	*tmp;

	tmp = node;
	if (node->type == NODE_CMD || node->type == NODE_SUBSHELL)
		tmp = node->left;
	while (tmp)
	{
		if (tmp->redir_type != REDIR_HEREDOC && tmp->args[1] != NULL)
			return (false);
		if (tmp->redir_type == REDIR_IN)
		{
			if (!ft_redir_in(node, tmp->value))
				return (ft_redir_error(tmp->value), false);
		}
		else
		{
			if (!ft_exec_redir_helper(node, tmp))
				return (false);
		}
		tmp = tmp->left;
	}
	return (true);
}
