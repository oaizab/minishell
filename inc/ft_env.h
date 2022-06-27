/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 10:03:08 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/21 11:18:53 by oaizab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ENV_H
# define FT_ENV_H

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

t_env	*ft_env_new(char *key, char *value);
void	ft_env_destroy(t_env *env);
void	ft_env_clear(t_env **env);
void	ft_env_add(t_env **env, char *key, char *value);
char	*ft_env_get(t_env *env, char *key);
t_env	*ft_env_init(char **env);
void	ft_export_add(t_env **env, char *key, char *value);
t_env	*ft_export_init(char **env);
void	ft_remove_env(t_env **env, char *key);
t_env	*ft_env_find(t_env *env, char *key);
bool	ft_validate_identifier(const char *identifier);
char	**ft_env_to_array(t_env *env);

#endif