/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 10:27:03 by hhamza            #+#    #+#             */
/*   Updated: 2022/06/02 11:25:44 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Create new token
 *
 * @param lexeme: Token lexeme (Token string)
 * @param type: Token type
 * @return t_token*: Newly created token or NULL on failure
 */
t_token	*ft_token_init(char *lexeme, t_token_type type)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (token == NULL)
	{
		return (NULL);
	}
	token->lexeme = lexeme;
	token->type = type;
	return (token);
}

/**
 * @brief Destroy token (Free all allocated memory)
 *
 * @param tok_addr: Address of token to destroy
 */
void	ft_token_destroy(void *tok_addr)
{
	t_token	*token;

	token = (t_token *) tok_addr;
	free(token->lexeme);
	free(token);
}

/**
 * @brief Add token to token list
 *
 * @param toklist: Token list
 * @param token_str: Address of token string
 * @param type: Token type
 */
void	ft_add_token(t_toklist **toklist, char **token_str, t_token_type type)
{
	t_token	*token;

	if (*token_str != NULL)
	{
		token = ft_token_init(*token_str, type);
		ft_lstadd_back(toklist, ft_lstnew(token));
		token = NULL;
		*token_str = NULL;
	}
}
