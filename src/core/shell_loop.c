/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 08:21:55 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/08 20:36:09 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	shell_loop(t_shell *shell)
{
	char	*line;
	t_cmd	cmd;

	while (1)
	{
		line = read_line();
		if (!line)
			break ;
		cmd = create_command(line);
		if (is_builtins(cmd.name))
			exec_builtins(cmd, shell);
		else
			exec_cmd(shell, line);
		if (cmd.args && cmd.args[0])
			free_array(cmd.args);
		free(line);
	}
}
