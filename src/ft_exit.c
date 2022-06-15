/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:41:21 by hhamza            #+#    #+#             */
/*   Updated: 2022/06/15 07:13:19 by hhamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Restore Ctrl-C echo, Clear command history, and exit.
 *
 * @param status: Exit status.
 */
void	ft_exit(int status)
{
	ft_restore_ctrl_c();
	rl_clear_history();
	exit(status);
}
