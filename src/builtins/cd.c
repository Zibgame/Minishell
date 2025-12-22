/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 10:51:52 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/22 17:30:20 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cd(t_shell *shell)
{
	char	*path;

	if (shell->in_pipeline)
		return (0);
	if (!shell->cmd->next || shell->cmd->next->type != ARGUMENT)
		return (1);
	path = shell->cmd->next->name;
	if (chdir(path) == -1)
	{
		printf("cd: no such file or directory: %s\n", path);
		return (1);
	}
	clean_command_free(shell);
	return (0);
}
