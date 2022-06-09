/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scanner.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 08:25:17 by hhamza            #+#    #+#             */
/*   Updated: 2022/06/09 17:11:58 by hhamza           ###   ########.fr       */
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
	scanner->size = ft_lstsize(toklist);
	scanner->curr_token = NULL;
	scanner->next_token = NULL;
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

	if (scanner->curr_token == NULL)
	{
		scanner->next_token = scanner->toklist;
	}
	scanner->curr_token = scanner->next_token;
	if (((t_token *) scanner->curr_token->content)->type == TOKEN_END)
	{
		return ((t_token *) scanner->next_token->content);
	}
	tokptr = scanner->next_token->content;
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
	if (scanner->curr_token == NULL)
	{
		return (get_next_token(scanner));
	}
	else
	{
		return (scanner->curr_token->content);
	}
}
