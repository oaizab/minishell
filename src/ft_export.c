/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 11:15:11 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/30 16:56:32 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Helper function for ft_export_add.
 *
 * @param env: ENV variable list address
 * @param new: New EXPORT variable node
 * @param key: Variable name
 */
static void	ft_export_add_helper(t_env **env, t_env *new, char *key)
{
	t_env	*tmp;

	if (!*env)
		*env = new;
	else if (strcmp(new->key, (*env)->key) < 0)
	{
		new->next = (*env);
		*env = new;
	}
	else
	{
		tmp = *env;
		while (tmp->next && ft_strcmp(tmp->next->key, key) < 0)
			tmp = tmp->next;
		new->next = tmp->next;
		tmp->next = new;
	}
}

/**
 * @brief Add new variable entry to EXPORT variable list.
 *
 * @param env: EXPORT variable list address
 * @param key: Variable name
 * @param value: Variable value
 */
void	ft_export_add(t_env **env, char *key, char *value)
{
	t_env	*new;
	t_env	*tmp;

	if (!env || !key)
		return ;
	tmp = ft_env_find(*env, key);
	if (tmp == NULL)
	{
		new = ft_env_new(key, value);
		if (new == NULL)
			return ;
		ft_export_add_helper(env, new, key);
	}
	else
	{
		if (value != NULL)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
		}
	}
}

/**
 * @brief Initialize EXPORT variable list.
 *
 * @param env: ENV variable list received from main
 * @return t_env*: New EXPORT variable list, NULL on failure
 */
t_env	*ft_export_init(char **env)
{
	t_env	*env_list;
	char	*key;
	char	*value;
	int		i;

	env_list = NULL;
	i = 0;
	if (!env)
		return (NULL);
	while (env[i])
	{
		key = ft_substr(env[i], 0, ft_strchr(env[i], '=') - env[i]);
		if (!key)
			return (ft_env_clear(&env_list), NULL);
		value = ft_strchr(env[i], '=') + 1;
		ft_export_add(&env_list, key, value);
		free(key);
		if (!env_list)
			return (NULL);
		i++;
	}
	(ft_remove_env(&env_list, "OLDPWD"), ft_export_add(&env_list, "OLDPWD", 0));
	return (env_list);
}
