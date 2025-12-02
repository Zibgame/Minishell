/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcadinot <zcadinot@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 08:21:55 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/02 09:25:26 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_loop(t_shell shell)
{
	char	*line;

	while (1)
	{
		line = read_line();
		if (!line)
			break ;
		exec_cmd(shell, line);
		free(line);
	}
}
