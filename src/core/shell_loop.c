/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 08:21:55 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/25 18:03:43 by dadoune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	create_command(t_shell *shell, char **line)
{
	shell->cmd = parse_command(*line);
	if (!shell->cmd || !shell->cmd->name)
		return ;
	expand_vars(shell);
	remove_empty_commands(&shell->cmd);
	extract_redirections(shell, shell->cmd);
	prepare_heredocs(shell, shell->cmd);
	recreate_line(shell, line);
}

static void	treat_fd(int save_in, int save_out)
{
	dup2(save_in, STDIN_FILENO);
	dup2(save_out, STDOUT_FILENO);
	close(save_in);
	close(save_out);
}

static void	this_is_builtin(t_shell *shell, char *line, int save_in,
	int save_out)
{
	save_in = dup(STDIN_FILENO);
	save_out = dup(STDOUT_FILENO);
	if (apply_redirections(shell->cmd))
	{
		shell->last_return = 1;
		treat_fd(save_in, save_out);
		ft_cmdclear(&shell->cmd);
		return ;
	}
	exec_builtins(shell, line);
	treat_fd(save_in, save_out);
	ft_cmdclear(&shell->cmd);
}

static void	main_loop(t_shell *shell, char *line, int save_in, int save_out)
{
	while (1)
	{
		line = readline(PS1);
		if (!line)
			break ;
		if (*line)
			add_history(line);
		create_command(shell, &line);
		if (shell->cmd)
		{
			if (has_pipe(shell->cmd))
				exec_pipeline(shell, line);
			else if (shell->cmd->type == BUILTINS)
				this_is_builtin(shell, line, save_in, save_out);
			else
				exec_cmd(shell, line);
			if (shell->cmd)
			{
				ft_cmdclear(&shell->cmd);
				shell->cmd = NULL;
			}
			free(line);
			line = NULL;
		}
	}
}

void	shell_loop(t_shell *shell)
{
	main_loop(shell, NULL, 0, 0);
	ft_printf_fd("exit\n", 1);
	free_shell(shell);
	close_fd();
	rl_clear_history();
	rl_free_line_state();
	rl_cleanup_after_signal();
}
