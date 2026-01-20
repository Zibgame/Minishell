/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcadinot <zcadinot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:59:48 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/20 11:26:04 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	exec_command(t_shell *shell, t_cmd *cmd)
{
	char	*path;
	char	**argv;

	if (cmd->type == BUILTINS)
		exit(exec_builtin_pipe(shell, cmd));
	if (!cmd->name)
		clean_exit(shell, 127, NULL, NULL);
	path = get_cmd_path(shell, cmd->name);
	if (!path)
		clean_exit(shell, 127, NULL, NULL);
	argv = build_argv(cmd);
	if (!argv)
		clean_exit(shell, 1, path, NULL);
	execve(path, argv, shell->envp_tmp);
	perror("minishell");
	clean_exit(shell, 126, path, argv);
}

void	exec_childda(t_shell *shell, t_pipedata data, char *line)
{
	signal_child();
	setup_child_fds(data);
	free(line);
	if (apply_redirections(data.cmd))
		clean_exit(shell, 1, NULL, NULL);
	exec_command(shell, data.cmd);
}

void	exec_pipeline(t_shell *shell, char *line)
{
	t_pipedata	data;
	int			cmd_error;

	cmd_error = check_commands_exist(shell);
	if (cmd_error)
	{
		shell->last_return = 127;
		ft_cmdclear(&shell->cmd);
		return ;
	}
	data.cmd = shell->cmd;
	data.in_fd = STDIN_FILENO;
	data.last_pid = -1;
	run_pipeline(shell, &data, line);
	ft_cmdclear(&shell->cmd);
	if (data.in_fd != -1 && data.in_fd != STDIN_FILENO)
		close(data.in_fd);
	if (data.last_pid != -1)
	{
		waitpid(data.last_pid, &data.status, 0);
		shell->last_return = get_exit_status(data.status);
	}
	while (wait(NULL) > 0)
		;
	print_cmd_not_found(shell->last_return);
}
