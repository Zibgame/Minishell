/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 08:21:55 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/05 13:43:25 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	shell_loop(t_shell *shell)
{
	char	*line;
	int		save_in;
	int		save_out;

	while (1)
	{
		line = read_line();
		if (!line)
			break ;
		shell->cmd = parse_command(line);
		extract_redirections(shell->cmd);
		if (shell->cmd)
		{
			if (has_pipe(shell->cmd))
				exec_pipeline(shell);
			else if (shell->cmd->type == BUILTINS)
			{
				save_in = dup(STDIN_FILENO);
				save_out = dup(STDOUT_FILENO);
				if (apply_redirections(shell->cmd))
				{
					dup2(save_in, STDIN_FILENO);
					dup2(save_out, STDOUT_FILENO);
					close(save_in);
					close(save_out);
					continue;
				}
				exec_builtins(shell);
				dup2(save_in, STDIN_FILENO);
				dup2(save_out, STDOUT_FILENO);
				close(save_in);
				close(save_out);
			}
			else
				exec_cmd(shell, line);
			add_history(line);
			free(line);
		}
	}
	free_shell(shell);
}
