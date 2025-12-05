/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 08:05:22 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/05 10:29:00 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "structs.h"
# include "librairies.h"

void	init_signal(void);
void	sig_handler(int sig);
void	shell_loop(t_shell shell);
void	start_shell(t_shell shell);
void	exec_cmd(t_shell shell, char *line);

char	*read_line(void);
char	*get_cmd(char *cmd, char **env);

t_shell	create_shell_struct(char **envp);

#endif
