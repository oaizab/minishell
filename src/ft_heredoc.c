/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:34:59 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/16 11:34:55 by oaizab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_heredoc(const char *delimiter)
{
	char	*str;
	char	*ret;

	str = readline("> ");
	ret = ft_strdup("");
	while (str != NULL && ft_strcmp(str, delimiter) != 0)
	{
		ret = ft_append_str(ret, str);
		ret = ft_append_char(ret, '\n');
		free(str);
		str = readline("> ");
	}
	free (str);
	return (ret);
}
