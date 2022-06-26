/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 11:44:17 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/25 18:18:27 by oaizab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_var_name(char *str)
{
	int		i;
	char	*var;

	i = 0;
	if (str[0] == '?')
		return (ft_strdup("?"));
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

static void	ft_expander_helper(t_ast_node *node, t_env *env, char **args, int k)
{
	char	**split;
	char	*str;
	int		i;
	int		j;

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
}

static void	ft_free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	ft_expander(t_ast_node *node, t_env *env)
{
	char	**split;
	char	**args;
	char	*str;
	int		i;
	int		k;

	i = 0;
	args = ft_calloc(ARG_MAX, sizeof(char *));
	if (args == NULL)
		return ;
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
		args[k++] = split[i++];
	(free(split), ft_expander_helper(node, env, args, k));
	if (node->args)
		ft_free_args(node->args);
	node->args = args;
}
