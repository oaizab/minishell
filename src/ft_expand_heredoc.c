/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 18:34:27 by hhamza            #+#    #+#             */
/*   Updated: 2022/06/30 10:08:37 by oaizab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Helper function for ft_expand_heredoc.
 *
 * @param var: Environement variable name to expand.
 * @param str: Expansion result string address.
 * @param i: Current index address.
 * @param env: Environement.
 */
static void	ft_heredoc_expander_helper(char *var, char **str, int *i, \
	t_env *env)
{
	char	*tmp;

	if (var[0] == '\0')
		*str = ft_append_char(*str, '$');
	else
	{
		*i += ft_strlen(var);
		tmp = ft_env_get(env, var, false);
		if (!tmp)
			tmp = "";
		*str = ft_append_str(*str, tmp);
	}
	free(var);
}

/**
 * @brief Cleanup helper function for ft_expand_heredoc (For norm reasons)
 *
 * @param node: AST node to be expanded
 * @param str: Expansion result string
 */
static void	ft_heredoc_expander_cleanup(t_ast_node *node, char *str)
{
	free(node->value);
	node->value = str;
}

/**
 * @brief Here-document (heredoc) expander. Expands environment variables only.
 *
 * @param node: AST node to expand.
 * @param env: Environment.
 * @return bool: True if expansion was successful, false otherwise.
 */
bool	ft_heredoc_expander(t_ast_node *node, t_env *env)
{
	char	*str;
	char	*var;
	int		i;

	i = -1;
	str = NULL;
	while (node->value[++i])
	{
		if (node->value[i] == '$')
		{
			var = ft_get_var_name(&node->value[i + 1]);
			if (var == NULL)
				return (free(str), false);
			ft_heredoc_expander_helper(var, &str, &i, env);
			if (str == NULL)
				return (false);
		}
		else
		{
			str = ft_append_char(str, node->value[i]);
			if (str == NULL)
				return (false);
		}
	}
	return (ft_heredoc_expander_cleanup(node, str), true);
}
