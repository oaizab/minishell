/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_asterisk_helpers.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 08:52:49 by hhamza            #+#    #+#             */
/*   Updated: 2022/06/24 08:53:32 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Count directory entries
 *
 * @param path: Directory path
 * @return int: Number of entries, 0 on failure
 */
int	ft_file_count(char *path)
{
	DIR	*dir;
	int	count;

	count = 0;
	dir = opendir(path);
	if (dir == NULL)
		return (0);
	while (readdir(dir) != NULL)
		count++;
	closedir(dir);
	return (count);
}

/**
 * @brief Get directory entries names that match pattern.
 *
 * @param files: Array of strings to store names
 * @param pattern: Pattern to match
 * @param i: Index of files array address
 * @return bool: True on success, false on failure
 */
bool	ft_get_dir_entries(char **files, char *pattern, int *i)
{
	DIR				*dir;
	struct dirent	*file;

	dir = opendir(".");
	if (dir == NULL)
		return (false);
	file = readdir(dir);
	while (file != NULL)
	{
		if (ft_check_pattern(file->d_name, pattern))
			files[(*i)++] = ft_strdup(file->d_name);
		file = readdir(dir);
	}
	closedir(dir);
	return (true);
}

/**
 * @brief Get patten matches on the current working directory joined in a
 * single string.
 *
 * @param pattern: Pattern to match
 * @return char*: String of matches, NULL on failure
 */
char	*ft_get_matches(char *pattern)
{
	int				i;
	char			**files;
	char			*str;

	i = ft_file_count(".");
	files = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	if (ft_get_dir_entries(files, pattern, &i) == false)
		return (free(files), ft_strdup(pattern));
	i = 0;
	str = NULL;
	if (files[0] == NULL)
		return (free(files), ft_strdup(pattern));
	while (files[i])
	{
		str = ft_append_str(str, files[i]);
		free(files[i++]);
		if (files[i])
			str = ft_append_char(str, ' ');
	}
	free(files);
	return (str);
}
