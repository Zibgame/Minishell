/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 08:21:55 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/09 15:24:18 by aeherve          ###   ########.fr       */
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
		free(line);
	}
}
