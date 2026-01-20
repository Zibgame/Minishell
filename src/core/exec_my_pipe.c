/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_my_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcadinot <zcadinot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:59:48 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/20 11:27:21 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

void	handle_fork_error(t_pipedata *data)
{
	if (data->in_fd != -1 && data->in_fd != STDIN_FILENO)
		close(data->in_fd);
	if (data->pipefd[1] != -1 && data->pipefd[1] != STDOUT_FILENO)
		close(data->pipefd[1]);
	if (data->pipefd[0] != -1)
		close(data->pipefd[0]);
}

void	clean_exit(t_shell *shell, int err_code, char *path, char **argv)
{
	if (path)
		free(path);
	if (argv)
		free_array(argv);
	free_shell(shell);
	exit(err_code);
}

int	check_commands_exist(t_shell *shell)
{
	t_cmd	*current;
	char	*path;
	int		found_error;

	found_error = 0;
	current = shell->cmd;
	while (current)
	{
		if (current->type != BUILTINS && current->type != PIPE
			&& current->type != REDIRECTION && current->name)
		{
			path = get_cmd_path(shell, current->name);
			if (!path && !ft_strchr(current->name, '/'))
			{
				if (!found_error)
					ft_printf_fd("minishell: %s: command not found\n",
						2, current->name);
				found_error = 1;
			}
			if (path)
				free(path);
		}
		current = get_next_cmd(current);
	}
	return (found_error);
}

void	print_cmd_not_found(int last_return)
{
	if (last_return != 0)
		ft_printf_fd("minishell: command not found\n", 2);
}
