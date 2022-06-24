/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 11:43:47 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/24 08:57:48 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXPANDER_H
# define FT_EXPANDER_H

void	ft_expander(t_ast_node *node, t_env *env);
bool	ft_heredoc_expander(t_ast_node *node, t_env *env);

char	*ft_get_var_name(char *str);
char	*ft_expand_str(char *value, t_env *env);

void	ft_expand_asterisk(char **value);
char	*ft_get_matches(char *pattern);
int		ft_file_count(char *path);
bool	ft_check_pattern(char *str, char *pattern);
bool	ft_get_dir_entries(char **files, char *pattern, int *i);

#endif