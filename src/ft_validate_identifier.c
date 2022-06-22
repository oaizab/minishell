/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validate_identifier.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 11:10:27 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/21 11:18:29 by oaizab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief validate identifier based on regex
 *
 * @regex: ^[a-zA-Z_][a-zA-Z0-9_]*$
 * @param identifier: String to validate
 * @return bool: true if valid, false if not
 */
bool	ft_validate_identifier(const char *identifier)
{
	int	i;

	if (!identifier)
		return (false);
	if (!ft_isalpha(identifier[0]) && identifier[0] != '_')
		return (false);
	i = 1;
	while (identifier[i] != '\0')
	{
		if (!ft_isalnum(identifier[i]) && identifier[i] != '_')
			return (false);
		i++;
	}
	return (true);
}
