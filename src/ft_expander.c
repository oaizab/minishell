/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 11:44:17 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/24 20:08:35 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_var_name(char *str)
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

char	*ft_expand_str(char *value, t_env *env)
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
	ft_expand_asterisk(&str);
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
		ft_expand_asterisk(&str);
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
