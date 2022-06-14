/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scanner.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 08:25:17 by hhamza            #+#    #+#             */
/*   Updated: 2022/06/13 09:14:45 by oaizab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_scanner.h"

/**
 * @brief Create a new scanner object
 *
 * @param toklist: Token list which the scanner will be based on
 * @return t_scanner*: Newly created scanner object
 */
t_scanner	*ft_scanner_new(t_toklist *toklist)
{
	t_scanner	*scanner;

	scanner = ft_calloc(1, sizeof(t_scanner));
	if (scanner == NULL)
	{
		return (NULL);
	}
	scanner->toklist = toklist;
	scanner->curr_token = toklist;
	scanner->next_token = toklist->next;
	return (scanner);
}

/**
 * @brief Destroy a scanner object
 *
 * @param scanner: Scanner object address
 */
void	ft_scanner_destroy(t_scanner **scanner)
{
	if (scanner == NULL)
	{
		return ;
	}
	ft_lstclear(&(*scanner)->toklist, &ft_token_destroy);
	free(*scanner);
	*scanner = NULL;
}

/**
 * @brief Get the next token object
 *
 * @param scanner: Scanner object
 * @return t_token*: Retreived token object
 */
t_token	*get_next_token(t_scanner *scanner)
{
	t_token			*tokptr;

	if (((t_token *) scanner->curr_token->content)->type == TOKEN_END)
	{
		return ((t_token *) scanner->curr_token->content);
	}
	tokptr = scanner->curr_token->content;
	scanner->curr_token = scanner->next_token;
	scanner->next_token = scanner->next_token->next;
	return (tokptr);
}

/**
 * @brief Peek the next token without retreiving it
 *
 * @param scanner: Scanner object
 * @return t_token*: Peeked token object
 */
t_token	*ft_scanner_peek(t_scanner *scanner)
{
	if (scanner->next_token == NULL)
	{
		return (scanner->curr_token->content);
	}
	else
	{
		return (scanner->curr_token->content);
	}
}
