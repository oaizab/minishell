/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 10:40:43 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/27 16:43:57 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Initialize new ENV variable list.
 *
 * @param env: ENV variables received from main
 * @return t_env*: New ENV variable list, NULL on failure
 */
t_env	*ft_env_init(char **env)
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
		ft_env_add(&env_list, key, value);
		free(key);
		if (!env_list)
			return (NULL);
		i++;
	}
	return (env_list);
}

/**
 * @brief Remove variable entry from ENV variable list.
 *
 * @param env: ENV variable list address
 * @param key: Variable name
 */
void	ft_remove_env(t_env **env, char *key)
{
	t_env	*tmp;
	t_env	*tmp2;

	if (!env || !key)
		return ;
	tmp = *env;
	if (!ft_strcmp(tmp->key, key))
	{
		*env = tmp->next;
		ft_env_destroy(tmp);
		return ;
	}
	while (tmp->next)
	{
		if (!ft_strcmp(tmp->next->key, key))
		{
			tmp2 = tmp->next;
			tmp->next = tmp->next->next;
			ft_env_destroy(tmp2);
			return ;
		}
		tmp = tmp->next;
	}
}

/**
 * @brief Find variable entry in ENV variable list.
 *
 * @param env: ENV variable list address
 * @param key: Variable name
 * @return t_env*: Variable entry, NULL on failure
 */
t_env	*ft_env_find(t_env *env, char *key)
{
	while (env != NULL)
	{
		if (!ft_strcmp(env->key, key))
			return (env);
		env = env->next;
	}
	return (NULL);
}

/**
 * @brief Convert ENV variable list into an array of string in form of
 * "key=value".
 *
 * @param env: ENV variable list
 * @return char**: Array of string, NULL on failure
 */
char	**ft_env_to_array(t_env *env)
{
	char	**env_all;
	t_env	*tmp;
	int		i;
	int		len;

	i = 0;
	env_all = NULL;
	tmp = env;
	len = 0;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	env_all = ft_calloc(len + 1, sizeof(char *));
	while (env)
	{
		env_all[i] = ft_strjoin(env->key, "=");
		env_all[i] = ft_append_str(env_all[i], env->value);
		env = env->next;
		i++;
	}
	return (env_all);
}
