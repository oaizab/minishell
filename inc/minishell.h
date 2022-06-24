/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:52:59 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/24 10:17:48 by oaizab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <string.h>
# include <signal.h>
# include <termios.h>
# include <dirent.h>

# include "libft.h"
# include "ft_lexer.h"
# include "ft_scanner.h"
# include "ft_ast.h"
# include "ft_parser.h"
# include "ft_error.h"
# include "ft_env.h"
# include "ft_builtin.h"
# include "ft_expander.h"
# include "ft_executor.h"

/**
 * @brief Minishell main header file.
 *
 * @globals:
 *  * g_exit_status: Exit status.
 *
 * @features:
 *  * ft_read_cmd: Read command.
 *  * ft_install_signal: Install custom signal handlers.
 *  * ft_uninstall_signals: Uninstall custom signal handlers.
 *  * ft_hide_ctrl_c: Hide Ctrl+C echo.
 *  * ft_show_ctrl_c: Restore Ctrl+C echo.
 *  * ft_exit: Exit minishell.
 */

extern int	g_exit_status;

char	*ft_read_cmd(void);

void	ft_install_signals(void);
void	ft_uninstall_signals(void);

void	ft_hide_ctrl_c(void);
void	ft_restore_ctrl_c(void);

void	ft_exit(int status);

#endif