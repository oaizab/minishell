/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_str_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 20:36:18 by hhamza            #+#    #+#             */
/*   Updated: 2022/06/24 20:42:13 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Free string array.
 *
 * @param arr: String array
 */
void	ft_free_str_array(char **arr)
{
	int i;

	i = 0;
	if (arr == NULL)
		return ;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
