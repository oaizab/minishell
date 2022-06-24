/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_matches.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 07:35:38 by hhamza            #+#    #+#             */
/*   Updated: 2022/06/24 08:49:55 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_expand_asterisk(char **value)
{
	char	*str;
	char	*tmp;
	char	*word;
	int		i;
	bool	is_asterisk;
	t_state	state;
	bool	no_expand;

	is_asterisk = false;
	no_expand = false;
	word = NULL;
	str = NULL;
	state = STATE_DEFAULT;
	i = 0;
	while ((*value)[i] != '\0')
	{
		if (state == STATE_DEFAULT)
		{
			if ((*value)[i] == ' ')
			{
				if (word)
				{
					if (is_asterisk)
					{
						tmp = ft_get_matches(word);
						free(word);
					}
					else
						tmp = word;
					str = ft_append_str(str, tmp);
				}
				str = ft_append_char(str, ' ');
				free(tmp);
				no_expand = false;
				is_asterisk = false;
				word = NULL;
			}
			else if ((*value)[i] == '*' && no_expand == false)
			{
				is_asterisk = true;
				word = ft_append_char(word, '*');
			}
			else
				word = ft_append_char(word, (*value)[i]);
		}
		else if (state == STATE_DQUOTE)
		{
			no_expand = true;
			is_asterisk = false;
			if ((*value)[i] == '"')
				state = STATE_DEFAULT;
			word = ft_append_char(word, (*value)[i]);
		}
		else if (state == STATE_QUOTE)
		{
			no_expand = true;
			is_asterisk = false;
			if ((*value)[i] == '\'')
				state = STATE_DEFAULT;
			word = ft_append_char(word, (*value)[i]);
		}
		i++;
	}
	if (word)
	{
		if (is_asterisk)
		{
			tmp = ft_get_matches(word);
			free(word);
		}
		else
			tmp = word;
		str = ft_append_str(str, tmp);
		free(tmp);
	}
	if (str == NULL)
		return ;
	free(*value);
	*value = str;
}
