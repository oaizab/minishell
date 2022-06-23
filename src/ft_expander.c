/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 11:44:17 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/23 17:58:29 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_get_var_name(char *str)
{
	int		i;
	char	*var;

	i = 0;
	var = ft_strdup("");
	if (var == NULL)
		return (NULL);
	if (str[0] != '_' && !ft_isalpha(str[0]))
		return (var);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
	{
		var = ft_append_char(var, str[i]);
		if (var == NULL)
			return (NULL);
		i++;
	}
	return (var);
}

char	**ft_split_args(char *value)
static char	**ft_split_args(char *value)
{
	t_state	state;
	char	**split;
	int		i;
	char	*str;
	int		j;

	i = 0;
	j = 0;
	split = ft_calloc(ARG_MAX, sizeof(char *));
	state = STATE_DEFAULT;
	str = NULL;
	if (!split)
		return (NULL);
	while (value[i])
	{
		if (state == STATE_DEFAULT)
		{
			if (value[i] == '\'')
				state = STATE_QUOTE;
			else if (value[i] == '"')
				state = STATE_DQUOTE;
			else if (value[i] == ' ')
			{
				if (str != NULL)
				{
					split[j] = str;
					str = NULL;
					j++;
				}
			}
			else
			{
				str = ft_append_char(str, value[i]);
			}
		}
		else if (state == STATE_DQUOTE)
		{
			if (value[i] == '"')
				state = STATE_DEFAULT;
			else
				str = ft_append_char(str, value[i]);
		}
		else if (state == STATE_QUOTE)
		{
			if (value[i] == '\'')
				state = STATE_DEFAULT;
			else
				str = ft_append_char(str, value[i]);
		}
		i++;
	}
	if (str != NULL)
	{
		split[j] = str;
		j++;
	}
	if (!split[0])
	{
		split[0] = ft_strdup("");
		if (!split[0])
			return (NULL); // TODO: free split array
	}
	return (split);
}

bool	ft_check_pattern(char *str, char *pattern)
{
	int	i;
	int	j;
	int	ilast;

	i = 0;
	j = 0;
	ilast = -1;
	if (str[0] == '.' && pattern[0] != '.')
		return (false);
	while (str[i] != '\0')
	{
		if (pattern[j] == '\0' && (str[i] == '\0' || pattern[j - 1] == '*'))
			return (true);
		else if (pattern[j] == '*')
		{
			while (pattern[j] == '*')
				j++;
			ilast = j;
		}
		if (str[i] == pattern[j])
		{
			i++;
			j++;
		}
		else
		{
			if (ilast == -1)
				return (false);
			if (ilast == j)
				i++;
			j = ilast;
		}
	}
	if (pattern[j] == '\0' || (pattern[j] == '*' && pattern[j + 1] == '\0'))
		return (true);
	return (false);
}

int	ft_file_count(char *path)
{
	DIR	*dir;
	int	count;

	count = 0;
	dir = opendir(path);
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

static char	*ft_expand_str(char *value, t_env *env)
{
	char	*str;
	char	*var;
	char	*tmp;
	t_state	state;
	int		i;

	i = 0;
	str = NULL;
	state = STATE_DEFAULT;
	while (value[i] != '\0')
	{
		if (state == STATE_DEFAULT)
		{
			if (value[i] == '$')
			{
				var = ft_get_var_name(&value[i + 1]);
				if (var[0] != '\0')
				{
					i += ft_strlen(var);
					tmp = ft_env_get(env, var);
					if (tmp == NULL)
						tmp = "";
					str = ft_append_str(str, tmp);
				}
				else
					str = ft_append_char(str, '$');
				free(var);
			}
			else
				str = ft_append_char(str, value[i]);
			if (value[i] == '\'')
				state = STATE_QUOTE;
			else if (value[i] == '"')
				state = STATE_DQUOTE;
		}
		else if (state == STATE_DQUOTE)
		{
			if (value[i] == '$')
			{
				var = ft_get_var_name(&value[i + 1]);
				if (var[0] != '\0')
				{
					i += ft_strlen(var);
					tmp = ft_env_get(env, var);
					if (tmp == NULL)
						tmp = "";
					str = ft_append_str(str, tmp);
				}
				else
					str = ft_append_char(str, '$');
				free(var);
			}
			else
				str = ft_append_char(str, value[i]);
			if (value[i] == '"')
				state = STATE_DEFAULT;
		}
		else if (state == STATE_QUOTE)
		{
			str = ft_append_char(str, value[i]);
			if (value[i] == '\'')
				state = STATE_DEFAULT;
		}
		i++;
	}
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

void	ft_expander(t_ast_node *node, t_env *env)
{
	char	**split;
	char	**args;
	char	*str;
	int		i;
	int		j;
	int		k;

	i = 0;
	args = ft_calloc(ARG_MAX, sizeof(char *));
	str = ft_expand_str(node->value, env);
	ft_asterisk_expand(&str);
	split = ft_split_args(str);
	free(str);
	if (!split)
		return ;
	free(node->value);
	node->value = ft_strdup(split[0]);
	k = 0;
	while (split[i] != NULL)
	{
		args[k] = split[i];
		i++;
		k++;
	}
	free(split);
	j = 1;
	while (node->args && node->args[j] != NULL)
	{
		str = ft_expand_str(node->args[j], env);
		ft_asterisk_expand(&str);
		split = ft_split_args(str);
		free(str);
		if (!split)
			return ;
		i = 0;
		while (split[i] != NULL)
		{
			args[k] = split[i];
			i++;
			k++;
		}
		free(split);
		j++;
	}
	i = 0;
	while (node->args && node->args[i] != NULL)
	{
		free(node->args[i]);
		i++;
	}
	free(node->args);
	node->args = args;
}
