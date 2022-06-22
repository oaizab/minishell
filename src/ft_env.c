/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 10:03:25 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/21 10:46:35 by oaizab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_env_new(char *key, char *value)
{
	t_env	*env;

	env = ft_calloc(1, sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = ft_strdup(key);
	env->value = ft_strdup(value);
	if (!env->key || !env->value)
	{
		free(env->key);
		free(env->value);
		free(env);
		return (NULL);
	}
	return (env);
}

void	ft_env_destroy(t_env *env)
{
	if (!env)
		return ;
	free(env->key);
	free(env->value);
	free(env);
}

void	ft_env_clear(t_env **env)
{
	t_env	*tmp;

	while (*env)
	{
		tmp = (*env)->next;
		ft_env_destroy(*env);
		*env = tmp;
	}
}

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
		if (tmp->next && ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			ft_env_destroy(new);
			tmp->value = ft_strdup(value);
		}
		else
			tmp->next = new;
	}
}

char	*ft_env_get(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
