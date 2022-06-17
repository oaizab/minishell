/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_command_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:25:56 by hhamza            #+#    #+#             */
/*   Updated: 2022/06/17 15:25:57 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Test if token is a command (Command list or opening parenthesis)
 *
 * @param type: Token type.
 * @return bool: True if token is a command, false otherwise.
 */
bool	ft_is_command(t_token_type type)
{
	return (ft_is_cmdlist(type) || type == TOKEN_OPAR);
}

/**
 * @brief Test if token is a binary operator (&&, ||, |)
 *
 * @param type: Token type.
 * @return bool: True if token is a binary operator, false otherwise.
 */
bool	ft_is_binary(t_token_type type)
{
	return (type == TOKEN_OR || type == TOKEN_AND || type == TOKEN_PIPE \
		|| type == TOKEN_END);
}

/**
 * @brief Test if parenthesis expression is closed
 *
 * @param type: Current token type.
 * @return bool: True if parenthesis expression is closed, false otherwise.
 */
bool	ft_is_closed(t_token_type type)
{
	return (type == TOKEN_CPAR || ft_is_binary(type));
}
