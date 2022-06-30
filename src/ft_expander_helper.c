/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 17:39:27 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/30 10:08:46 by oaizab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_var_helper(char **tmp, char *var, t_env *env)
{
	if (var[0] == '?')
		*tmp = ft_itoa(g_exit_status);
	else
	{
		*tmp = ft_env_get(env, var, false);
		if (*tmp != NULL)
			*tmp = ft_strdup(*tmp);
	}
	if (*tmp == NULL)
		*tmp = ft_strdup("");
}

static void	ft_state_helper(char *curr_char, int *i, char **str, \
	t_env *env)
{
	char	*tmp;
	char	*var;

	if (*curr_char == '$')
	{
		var = ft_get_var_name(&curr_char[1]);
		if (var[0] != '\0')
		{
			*i += ft_strlen(var);
			ft_var_helper(&tmp, var, env);
			*str = ft_append_str(*str, tmp);
			(free(var), free (tmp));
		}
		else
			*str = (free(var), ft_append_char(*str, '$'));
	}
	else
		*str = ft_append_char(*str, *curr_char);
}

static void	ft_state_quote(char curr_char, t_state *state, char **str)
{
	if (*state == STATE_QUOTE)
	{
		*str = ft_append_char(*str, curr_char);
		if (curr_char == '\'')
			*state = STATE_DEFAULT;
	}
}

static void	ft_init_expander_helper(t_state *state, char **str, int *i)
{
	*i = -1;
	*str = NULL;
	*state = STATE_DEFAULT;
}

char	*ft_expand_str(char *value, t_env *env)
{
	char	*str;
	t_state	state;
	int		i;

	ft_init_expander_helper(&state, &str, &i);
	while (value[++i] != '\0')
	{
		if (state == STATE_DEFAULT)
		{
			ft_state_helper(&value[i], &i, &str, env);
			if (value[i] == '\'')
				state = STATE_QUOTE;
			else if (value[i] == '"')
				state = STATE_DQUOTE;
		}
		else if (state == STATE_DQUOTE)
		{
			ft_state_helper(&value[i], &i, &str, env);
			if (value[i] == '"')
				state = STATE_DEFAULT;
		}
		else
			ft_state_quote(value[i], &state, &str);
	}
	return (str);
}
