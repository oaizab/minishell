/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_pattern.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 08:08:10 by hhamza            #+#    #+#             */
/*   Updated: 2022/06/24 08:30:35 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Helper function for ft_check_pattern. Skip any characters (Matching
 * asterisk in pattern)
 *
 * @param ilast: Index of last found non-asterisk character after a sequence of
 * asterisks
 * @param i: String to check current index address
 * @param j: Pattern to check current index address
 */
static void	ft_check_pattern_helper(int ilast, int *i, int *j)
{
	if (ilast == *j)
		(*i)++;
	*j = ilast;
}

/**
 * @brief Skip asterisks
 *
 * @param pattern: Pattern string to skip asterisks in
 * @param j: Pattern current index address
 * @param ilast: Index address of first found non-asterisk character
 */
static void	ft_skip_asterisks(char *pattern, int *j, int *ilast)
{
	while (pattern[*j] == '*')
		(*j)++;
	*ilast = *j;
}

/**
 * @brief Literally increment i and j
 *
 * @param i: i address
 * @param j: j address
 */
static void	ft_increment_i_and_j(int *i, int *j)
{
	(*i)++;
	(*j)++;
}

/**
 * @brief Check if string validates pattern
 *
 * @param str: String to check
 * @param pattern: Pattern to check
 * @return bool: True if string validates pattern, false otherwise
 * @note: The "0" on the last line is meant to be '\0' (Norm reasons)
 */
bool	ft_check_pattern(char *str, char *pattern)
{
	int	i;
	int	j;
	int	ilast;

	i = 0;
	j = 0;
	ilast = -1;
	if (str[0] == '.' && pattern[0] != '.')
		return (false);
	while (str[i] != '\0')
	{
		if (pattern[j] == '\0' && (str[i] == '\0' || pattern[j - 1] == '*'))
			return (true);
		else if (pattern[j] == '*')
			ft_skip_asterisks(pattern, &j, &ilast);
		if (str[i] == pattern[j])
			ft_increment_i_and_j(&i, &j);
		else
		{
			if (ilast == -1)
				return (false);
			ft_check_pattern_helper(ilast, &i, &j);
		}
	}
	return (pattern[j] == '\0' || (pattern[j] == '*' && pattern[j + 1] == 0));
}
