/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 10:03:25 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/29 20:09:02 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Create a new ENV variable node.
 *
 * @param key: Variable name
 * @param value: Variable value
 * @return t_env*: New ENV variable node, NULL on failure
 */
t_env	*ft_env_new(char *key, char *value)
{
	t_env	*env;

	env = ft_calloc(1, sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = ft_strdup(key);
	if (value != NULL)
	{
		env->value = ft_strdup(value);
		if (env->value == NULL)
			return (free(env->key), free(env), NULL);
	}
	else
	{
		free(env->value);
		env->value = NULL;
	}
	if (!env->key)
		return (free(env->key), free(env->value), free(env), NULL);
	return (env);
}

/**
 * @brief Destroy an ENV variable node.
 *
 * @param env: ENV variable node address
 */
void	ft_env_destroy(t_env *env)
{
	if (!env)
		return ;
	free(env->key);
	free(env->value);
	free(env);
}

/**
 * @brief Clear ENV variable list.
 *
 * @param env : ENV variable list address
 */
void	ft_env_clear(t_env **env)
{
	t_env	*tmp;

	if (env == NULL || *env == NULL)
	{
		return ;
	}
	while (*env)
	{
		tmp = (*env)->next;
		ft_env_destroy(*env);
		*env = tmp;
	}
}

/**
 * @brief Add or replace an ENV variable.
 *
 * @param env: ENV variable list address
 * @param key: Variable name
 * @param value: Variable value
 */
void	ft_env_add(t_env **env, char *key, char *value)
{
	t_env	*new;
	t_env	*tmp;

	if (!env || !key || !value)
		return ;
	new = ft_env_new(key, value);
	if (!new)
		ft_env_clear(env);
	else if (!*env)
		*env = new;
	else
	{
		tmp = *env;
		while (tmp->next && ft_strcmp(tmp->key, key) != 0)
			tmp = tmp->next;
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			ft_env_destroy(new);
			tmp->value = ft_strdup(value);
		}
		else
			tmp->next = new;
	}
}

/**
 * @brief Get ENV variable value.
 *
 * @param env: ENV variable list
 * @param key: Variable name
 * @return char*: Variable value, NULL on failure
 */
char	*ft_env_get(t_env *env, char *key)
{
	static char	*path = "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.";

	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env->value);
		env = env->next;
	}
	if (!ft_strcmp(key, "PATH"))
		return (path);
	return (NULL);
}
