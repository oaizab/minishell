/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 11:15:11 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/22 18:11:58 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_export_add_helper(t_env **env, t_env *new, char *key)
{
	t_env	*tmp;

	if (!*env)
		*env = new;
	else if (strcmp(key, (*env)->key) < 0)
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

void	ft_export_add(t_env **env, char *key, char *value)
{
	t_env	*new;
	t_env	*tmp;

	if (!env || !key || !value)
		return ;
	tmp = ft_env_find(*env, key);
	if (tmp != NULL)
	{
		free(tmp->value);
		tmp->value = ft_strdup(value);
		return ;
	}
	if (strcmp(key, "_") == 0)
		return ;
	new = ft_env_new(key, value);
	if (!new)
	{
		ft_env_clear(env);
		return ;
	}
	ft_export_add_helper(env, new, key);
}

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
	return (env_list);
}
