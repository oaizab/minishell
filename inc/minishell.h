/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamza <hhamza@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:52:59 by oaizab            #+#    #+#             */
/*   Updated: 2022/05/25 15:49:14 by hhamza           ###   ########.fr       */
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

# include "utils.h"
# include "libft.h"
# include "lexer.h"

char	*read_cmd(void);

void	install_signals(void);
void	uninstall_signals(void);

void	hide_ctrl_c(void);
void	show_ctrl_c(void);

void	ft_exit(int status);

#endif