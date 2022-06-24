/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_matches.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 07:35:38 by hhamza            #+#    #+#             */
/*   Updated: 2022/06/24 08:49:55 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Helper function for ft_expand_asterisk when a word is gathered,
 * the word will expanded if it contains an asterisk
 *
 * @param word: Address of the word gathered so far
 * @param str: Address of string that will hold the expand result
 * @param is_asterisk: Address of boolean that indicates if the word contains
 * an asterisk or not
 * @param no_expand: Address of boolean that indicates if the word should be
 * expanded or not
 */
static void	ft_expand_word(char **word, char **str, int *expand)
{
	char	*tmp;

	tmp = NULL;
	if (*word)
	{
		if (*expand == 1)
		{
			tmp = ft_get_matches(*word);
			free(*word);
		}
		else
			tmp = *word;
		*str = ft_append_str(*str, tmp);
	}
	*str = ft_append_char(*str, ' ');
	free(tmp);
	*expand = 0;
	word = NULL;
}

/**
 * @brief Helper function for default state on ft_expand_asterisk
 *
 * @param curr_char: Current character
 * @param no_expand: Boolean indicating if expansion shall be performed or not
 * @param is_asterisk: Address if boolean indicating if the word contains an
 *  asterisk or not
 * @param word: Address of the word gathered so far
 */
static void	ft_default_state_help(char curr_char, int *expand, char **word)
{
	if (curr_char == '*' && *expand != 2)
	{
		*expand = 1;
		*word = ft_append_char(*word, '*');
	}
	else
		*word = ft_append_char(*word, curr_char);
}

/**
 * @brief Helper function for single/double quote state on ft_expand_asterisk
 *
 * @param expand: Address of boolean indicating if expansion shall be performed
 * @param curr_char: Current character
 * @param state: State address
 * @param word: Address of the word gathered so far
 */
static void	ft_state_quote_helper(int *expand, char curr_char, t_state *state, \
	char **word)
{
	if (*state == STATE_DQUOTE)
	{
		*expand = 2;
		if (curr_char == '"')
			*state = STATE_DEFAULT;
		*word = ft_append_char(*word, curr_char);
	}
	else if (*state == STATE_QUOTE)
	{
		*expand = 2;
		if (curr_char == '\'')
			*state = STATE_DEFAULT;
		*word = ft_append_char(*word, curr_char);
	}
}

/**
 * @brief Initializer function for ft_expand_asterisk
 *
 * @param expand: Address of boolean indicating if expansion shall be performed
 * @param word: Address of the word gathered so far
 * @param str: Address of string that will hold the expand result
 * @param state: State address
 */
static void	ft_initialize(int *expand, char **word, char **str, t_state *state)
{
	*expand = 0;
	*word = NULL;
	*str = NULL;
	*state = STATE_DEFAULT;
}

/**
 * @brief Expand asterisks.
 *
 * @param value: Address of AST node value
 */
void	ft_expand_asterisk(char **value)
{
	char	*str;
	char	*word;
	int		i;
	t_state	state;
	int		expand;

	ft_initialize(&expand, &word, &str, &state);
	i = 0;
	while ((*value)[i] != '\0')
	{
		if (state == STATE_DEFAULT)
		{
			if ((*value)[i] == ' ')
				ft_expand_word(&word, &str, &expand);
			ft_default_state_help((*value)[i], &expand, &word);
		}
		else
			ft_state_quote_helper(&expand, (*value)[i], &state, &word);
		i++;
	}
	ft_expand_word(&word, &str, &expand);
	if (str == NULL)
		return ;
	free(*value);
	*value = str;
}
