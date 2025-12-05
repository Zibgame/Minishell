/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 08:21:55 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/05 10:29:50 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
