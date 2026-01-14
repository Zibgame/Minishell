/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 08:21:55 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/14 15:42:02 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**cmdtoarg(t_cmd *cmd)
{
	int		i;
	char	**tmp;

	if (!cmd)
		return (NULL);
	tmp = ft_calloc(ft_cmdsize(cmd) + 1, sizeof(char *));
	if (!tmp)
		return (NULL);
	i = 0;
	while (cmd)
	{
		tmp[i] = ft_strdup(cmd->name);
		i++;
		cmd = cmd->next;
	}
	return (tmp);
}

static void	recreate_line(t_shell *shell, char **line)
{
	int		i;
	char	**args;
	char	*new_line;

	args = cmdtoarg(shell->cmd);
	if (!args)
		return ;
	new_line = ft_calloc(1, sizeof(char));
	if (!new_line)
	{
		free_array(args);
		return ;
	}
	i = 0;
	while (args[i])
	{
		new_line = join_and_free(new_line, args[i]);
		free(args[i]);
		if (args[i + 1])
			new_line = join_and_free(new_line, " ");
		i++;
	}
	free(args);
	free(*line);
	*line = new_line;
}

static void	create_command(t_shell *shell, char **line)
{
	shell->cmd = parse_command(*line);
	if (!shell->cmd)
		return ;
	expand_vars(shell);
	remove_empty_commands(&shell->cmd);
	extract_redirections(shell->cmd);
	prepare_heredocs(shell->cmd);
	recreate_line(shell, line);
}

static void	treat_fd(int save_in, int save_out)
{
	dup2(save_in, STDIN_FILENO);
	dup2(save_out, STDOUT_FILENO);
	close(save_in);
	close(save_out);
}

void	shell_loop(t_shell *shell)
{
	char	*line;
	int		save_in;
	int		save_out;

	line = NULL;
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
				exec_pipeline(shell);
			else if (shell->cmd->type == BUILTINS)
			{
				save_in = dup(STDIN_FILENO);
				save_out = dup(STDOUT_FILENO);
				if (apply_redirections(shell->cmd))
				{
					treat_fd(save_in, save_out);
					ft_cmdclear(&shell->cmd);
					break ;
				}
				exec_builtins(shell);
				treat_fd(save_in, save_out);
				ft_cmdclear(&shell->cmd);
			}
			else
				exec_cmd(shell, line);
		}
		free(line);
		line = NULL;
	}
	if (line)
		free(line);
	free_shell(shell);
	rl_clear_history();
	rl_free_line_state();
	rl_cleanup_after_signal();
}
