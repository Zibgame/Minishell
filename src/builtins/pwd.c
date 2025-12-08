/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcadinot <zcadinot@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 17:00:18 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/08 20:43:00 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pwd(t_cmd *cmd, t_shell *shell)
{
	char	buff[4096];
	char	*path;

	(void)cmd;
	(void)shell;
	path = getcwd(buff, 4096);
	if (!path)
	{
		printf("pwd: error retrieving current directory\n");
		return (1);
	}
	if (cmd->args[1])
	{
		printf("pwd: ignoring non-option arguments\n");
	}
	printf("%s\n", path);
	return (0);
}
