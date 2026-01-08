/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 09:04:17 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/07 18:40:32 by dadoune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	return_type(t_shell *shell, char *line)
{
	if (!ft_strncmp("$", line, 1) && ft_strncmp("$?", line, 2)
		&& ft_strlen(line) > 1)
		shell->last_return = 0;
	else
		shell->last_return = 127;
}

static int	handle_direct_path(t_shell *shell, char *cmd)
{
	struct stat	st;

	if (stat(cmd, &st) != 0)
	{
		ft_printf_fd("minishell: %s: No such file or directory\n", 2, cmd);
		shell->last_return = 127;
		return (1);
	}
	if (S_ISDIR(st.st_mode))
	{
		ft_printf_fd("minishell: %s: Is a directory\n", 2, cmd);
		shell->last_return = 126;
		return (1);
	}
	if (access(cmd, X_OK) != 0)
	{
		ft_printf_fd("minishell: %s: Permission denied\n", 2, cmd);
		shell->last_return = 126;
		return (1);
	}
	return (0);
}

static void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
		free(args[i++]);
	free(args);
}

void	exec_cmd(t_shell *shell, char *line)
{
	pid_t	pid;
	int		status;
	char	**args;
	char	*path;

	args = ft_split(line, ' ');
	if (!args)
		return ;
	args = clean_empty_args(args);
	if (!args || !args[0])
		return (free_args(args));
	if (ft_strchr(args[0], '/'))
	{
		if (handle_direct_path(shell, args[0]))
			return (free_args(args));
		path = ft_strdup(args[0]);
	}
	else
		path = get_cmd_path(shell, args[0]);
	if (!path)
	{
		ft_printf_fd("minishell: %s: command not found\n", 2, args[0]);
		return_type(shell, line);
		return (free_args(args));
	}
	pid = fork();
	if (pid == 0)
	{
		apply_redirections(shell->cmd);
		execve(path, args, shell->envp_tmp);
		perror("execve");
		exit(126);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->last_return = WEXITSTATUS(status);
	free(path);
	free_args(args);
}
