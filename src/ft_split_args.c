/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 20:07:56 by hhamza            #+#    #+#             */
/*   Updated: 2022/06/28 17:58:05 by oaizab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Helper function for ft_split_args. Manages single/double quotes
 * on splitting arguments.
 *
 * @param state: Current state of the expander.
 * @param curr_char: Current character to be handled.
 * @param str: Address of the string that contais the word
 */
static void	ft_quote_state_helper(t_state *state, char curr_char, char **str)
{
	if (*state == STATE_DQUOTE)
	{
		if (curr_char == '"')
			*state = STATE_DEFAULT;
		else
			*str = ft_append_char(*str, curr_char);
	}
	else if (*state == STATE_QUOTE)
	{
		if (curr_char == '\'')
			*state = STATE_DEFAULT;
		else
			*str = ft_append_char(*str, curr_char);
	}
}

/**
 * @brief Helper initialization function for ft_split_args.
 *
 * @param i: Address of current index on value string
 * @param j: Address of current index on split array
 * @param str: Address of the string that contais the word
 * @param split: Address of the split array
 * @return bool: true on success, false on failure
 */
static bool	ft_split_args_init(int *i, int *j, char **str, char ***split)
{
	*i = -1;
	*j = 0;
	*str = NULL;
	*split = ft_calloc(ARG_MAX, sizeof(char *));
	if (*split == NULL)
		return (false);
	return (true);
}

/**
 * @brief Helper function to run at the end of ft_split_args.
 *
 * @param str: String that contais the word
 * @param split: Split array
 * @param j: Address of split array current index
 * @return char**: Split array, NULL on failure
 */
static char	**ft_split_args_end(char *str, char **split, int *j)
{
	if (str != NULL)
	{
		split[*j] = str;
		(*j)++;
	}
	if (!split[0])
	{
		split[0] = ft_strdup("");
		if (!split[0])
			return (ft_free_str_array(split), NULL);
	}
	return (split);
}

/**
 * @brief Add word to split array.
 *
 * @param split: Split array
 * @param j: Address of current index on split array
 * @param str: Address of the string that contais the word
 */
static void	ft_add_word_to_split(char **split, int *j, char **str)
{
	if (*str != NULL)
	{
		split[*j] = *str;
		*str = NULL;
		(*j)++;
	}
}

char	**ft_split_args(char *value)
{
	t_state	state;
	char	**split;
	int		i[2];
	char	*str;

	state = STATE_DEFAULT;
	if (ft_split_args_init(&i[0], &i[1], &str, &split) == false)
		return (NULL);
	while (value[++i[0]])
	{
		if (state == STATE_DEFAULT)
		{
			if (value[i[0]] == '\'')
				state = STATE_QUOTE;
			else if (value[i[0]] == '"')
				state = STATE_DQUOTE;
			else if (value[i[0]] == ' ')
				ft_add_word_to_split(split, &i[1], &str);
			else
				str = ft_append_char(str, value[i[0]]);
		}
		else
			ft_quote_state_helper(&state, value[i[0]], &str);
	}
	return (ft_split_args_end(str, split, &i[1]));
}
