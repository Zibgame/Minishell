/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 08:21:55 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/16 03:04:39 by dadoune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	shell_loop(t_shell *shell)
{
	char	*line;
	
	while (1)
	{
		line = read_line();
		if (!line)
			break ;
		shell->cmd = parse_command(line);
		// display_list(shell->cmd);
		if (shell->cmd)
		{
			if (shell->cmd->type == BUILTINS)
				exec_builtins(shell);
			else
				exec_cmd(shell, line);
			add_history(line);
			free(line);
		}
	}
}
