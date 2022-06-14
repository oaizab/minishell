/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 18:17:08 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/14 14:33:10 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERROR_H
# define FT_ERROR_H

typedef enum e_error
{
	ERR_MALLOC,
	ERR_SYNTAX,
	ERR_CPAR
}				t_error;

void	ft_error(t_error err, t_token *token);

#endif