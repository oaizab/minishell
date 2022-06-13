/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaizab <oaizab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:52:59 by oaizab            #+#    #+#             */
/*   Updated: 2022/06/12 18:55:14 by oaizab           ###   ########.fr       */
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

# include "libft.h"
# include "ft_lexer.h"
# include "ft_scanner.h"
# include "ft_ast.h"
# include "ft_parser.h"
# include "ft_error.h"

char	*ft_read_cmd(void);

void	ft_install_signals(void);
void	ft_uninstall_signals(void);

void	ft_hide_ctrl_c(void);
void	ft_restore_ctrl_c(void);

void	ft_exit(int status);

#endif