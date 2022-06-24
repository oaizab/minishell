/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_asterisk.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 07:35:38 by hhamza            #+#    #+#             */
/*   Updated: 2022/06/24 08:08:40 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Count directory entries
 *
 * @param path: Directory path
 * @return int: Number of entries
 */
int	ft_file_count(char *path)
{
	DIR	*dir;
	int	count;

	count = 0;
	dir = opendir(path);
	if (dir == NULL)
		return (0);
	while (readdir(dir) != NULL)
		count++;
	closedir(dir);
	return (count);
}

char	*ft_expand_asterisk(char *pattern)
{
	int				i;
	DIR				*dir;
	struct dirent	*file;
	char			**files;
	char			*str;

	i = ft_file_count(".");
	files = calloc(i + 1, sizeof(char *));
	i = 0;
	dir = opendir(".");
	if (dir == NULL)
		return (free(files), ft_strdup(pattern));
	file = readdir(dir);
	while (file != NULL)
	{
		if (ft_check_pattern(file->d_name, pattern))
			files[i++] = ft_strdup(file->d_name);
		file = readdir(dir);
	}
	closedir(dir);
	i = 0;
	str = NULL;
	if (files[0] == NULL)
		return (free(files), ft_strdup(pattern));
	while (files[i])
	{
		str = ft_append_str(str, files[i]);
		free(files[i++]);
		if (files[i])
			str = ft_append_char(str, ' ');
	}
	free(files);
	return (str);
}

void	ft_asterisk_expand(char **value)
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
						tmp = ft_expand_asterisk(word);
						if (tmp == NULL)
							tmp = NULL;
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
			tmp = ft_expand_asterisk(word);
			free(word);
		}
		else
			tmp = word;
		str = ft_append_str(str, tmp);
	}
	str = ft_append_char(str, ' ');
	free(tmp);
	free(*value);
	*value = str;
}
