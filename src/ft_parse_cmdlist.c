/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_cmdlist.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:25:45 by hhamza            #+#    #+#             */
/*   Updated: 2022/06/26 13:31:53 by oaizab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Test if token is a command list (Argument or redirection)
 *
 * @param type: Token type.
 * @return bool: True if token is a command list, false otherwise.
 */
bool	ft_is_cmdlist(t_token_type type)
{
	return (type == TOKEN_WORD || ft_is_redir(type));
}

/**
 * @brief Helper function for ft_parse_cmdlist.
 *
 * @param scanner: Scanner object.
 * @param cmdlist: Command list node.
 * @return bool: false if ft_parse_cmdlist shall return NULL, true otherwise.
 */
static bool	ft_redirlist(t_scanner *scanner, t_ast_node **cmdlist)
{
	if (ft_is_redir(ft_scanner_peek(scanner)->type))
	{
		(*cmdlist)->left = ft_parse_redir(scanner);
		if ((*cmdlist)->left == NULL)
			return (false);
		while ((*cmdlist)->left != NULL)
			*cmdlist = (*cmdlist)->left;
	}
	return (true);
}

/**
 * @brief Helper function for ft_parse_cmdlist.
 *
 * @param scanner: Scanner object.
 * @param cmdlist: Command list node.
 * @param cmdtmp: Temporary command node.
 * @param i: Iterator integer
 * @return bool: false if ft_parse_cmdlist shall return NULL, true otherwise.
 */
static bool	ft_cmdlist(t_scanner *scanner, t_ast_node **cmdlist, \
	t_ast_node **cmdtmp, int i)
{
	t_token		*token;

	if (ft_scanner_peek(scanner)->type == TOKEN_WORD)
	{
		token = get_next_token(scanner);
		(*cmdtmp)->value = ft_strdup(token->lexeme);
		if ((*cmdtmp)->value == NULL)
			return (ft_ast_free(*cmdtmp), ft_error(ERR_MALLOC, NULL), false);
		(*cmdtmp)->type = NODE_CMD;
		(*cmdtmp)->args = ft_calloc(ARG_MAX, sizeof(char *));
		if ((*cmdtmp)->args == NULL)
			return (ft_ast_free(*cmdtmp), ft_error(ERR_MALLOC, NULL), false);
		(*cmdtmp)->args[0] = ft_strdup(token->lexeme);
		if ((*cmdtmp)->args[0] == NULL || !ft_redirlist(scanner, cmdlist))
			return (ft_ast_free(*cmdtmp), false);
		while (ft_scanner_peek(scanner)->type == TOKEN_WORD)
		{
			token = get_next_token(scanner);
			(*cmdtmp)->args[i++] = ft_strdup(token->lexeme);
			if (!(*cmdtmp)->args[i - 1] || !ft_redirlist(scanner, cmdlist))
				return (ft_ast_free(*cmdtmp), false);
		}
	}
	return (true);
}

/**
 * @brief Parse a command line.
 *
 * @param scanner: Scanner object.
 * @return t_ast_node*: Command line node, NULL on failure.
 */
t_ast_node	*ft_parse_cmdlist(t_scanner *scanner)
{
	t_ast_node	*cmdlist;
	t_ast_node	*cmdtmp;

	cmdlist = ft_ast_node_new(NODE_NOCMD, NULL);
	if (cmdlist == NULL)
		return (NULL);
	cmdtmp = cmdlist;
	if (!ft_redirlist(scanner, &cmdlist))
		return (ft_ast_free(cmdtmp), NULL);
	if (!ft_cmdlist(scanner, &cmdlist, &cmdtmp, 1))
		return (NULL);
	if (cmdtmp->type == NODE_NOCMD)
	{
		cmdlist = cmdtmp->left;
		cmdtmp->left = NULL;
		return (ft_ast_free(cmdtmp), cmdlist);
	}
	else
	{
		cmdtmp->in = STDIN_FILENO;
		cmdtmp->out = STDOUT_FILENO;
	}
	return (cmdtmp);
}
