/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 18:17:08 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/15 11:05:50 by oaizab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERROR_H
# define FT_ERROR_H

/**
 * @brief Error API.
 *
 * @datatypes:
 *  * t_error: Error types enumeration.
 *
 * @features:
 * * ft_error: Print an error message depending on the error type.
 */

typedef enum e_error
{
	ERR_MALLOC,
	ERR_SYNTAX,
	ERR_CPAR,
	ERR_QUOTE
}				t_error;

void	ft_error(t_error err, t_token *token);

#endif