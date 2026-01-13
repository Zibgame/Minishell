/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 08:21:55 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/13 19:00:31 by dadoune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**cmdtoarg(t_cmd *cmd)
{
	int		i;
	char	**tmp;

	if (cmd)
	{
		tmp = ft_calloc(1, sizeof(char *) * (ft_cmdsize(cmd) + 1));
		i = 0;
		while (cmd)
		{
			tmp[i] = ft_strdup(cmd->name);
			i++;
			cmd = cmd->next;
		}
		return (tmp);
	}
	return (NULL);
}

static void	recreate_line(t_shell *shell, char **line)
{
	int		i;
	char	**args;

	args = cmdtoarg(shell->cmd);
	if (!args)
		return ;
	i = 0;
	free(*line);
	*line = ft_calloc(1, sizeof(char));
	while (i < ft_cmdsize(shell->cmd))
	{
		*line = join_and_free(*line, args[i++]);
		if (i < ft_cmdsize(shell->cmd))
			*line = join_and_free(*line, " ");
	}
	free_array(args);
}

static void	create_command(t_shell *shell, char **line)
{
	shell->cmd = parse_command(*line);
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

	while (1)
	{
		line = read_line();
		if (!line)
			break ;
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
					continue ;
				}
				exec_builtins(shell);
				treat_fd(save_in, save_out);
			}
			else
				exec_cmd(shell, line);
			free(line);
		}
	}
	free_shell(shell);
}
