/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcadinot <zcadinot@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 10:51:52 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/09 11:15:06 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cd(t_cmd *cmd, t_shell *shell)
{
	char	*path;

	(void)shell;
	if (!cmd->args[1])
		return (1);
	path = cmd->args[1];
	if (!path)
		return (1);
	if (chdir(path) == -1)
	{
		printf("cd: no such file or directory: %s\n", path);
		return (1);
	}
	return (0);
}
