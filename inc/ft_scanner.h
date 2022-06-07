/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scanner.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:40:46 by hhamza            #+#    #+#             */
/*   Updated: 2022/06/07 10:31:33 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SCANNER_H
# define FT_SCANNER_H

# include "ft_lexer.h"

/**
 * @brief API that reads from a token list
 *
 * @features:
 * 	* ft_scanner_new: Create a new scanner object.
 *	* get_next_token: Return the next token in the token list.
 *	* ft_scanner_peek: Peek the next token without retreiving it.
 *	* ft_scanner_destroy: Destroy the scanner object.
 */

typedef struct s_scanner
{
	t_toklist	*toklist;
	size_t		size;
	t_toklist	*curr_token;
	t_toklist	*next_token;
}	t_scanner;

t_scanner	*ft_scanner_new(t_toklist *tokens);
t_token		*get_next_token(t_scanner *scanner);
t_token		*ft_scanner_peek(t_scanner *scanner);
void		ft_scanner_destroy(t_scanner **scanner);

#endif
