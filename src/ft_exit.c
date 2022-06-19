/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:41:21 by hhamza            #+#    #+#             */
/*   Updated: 2022/06/19 08:31:47 by oaizab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

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
