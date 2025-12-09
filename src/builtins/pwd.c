/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 17:00:18 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/09 10:30:52 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pwd(t_cmd *cmd, t_shell *shell)
{
	// char	buff[2048];
	// char	*path;

	(void)cmd;
	// (void)shell;
	// path = getcwd(buff, 2048);
	// if (!path)
	// {
	// 	printf("pwd: error retrieving current directory\n");
	// 	return (1);
	// }
	if (cmd->args[1])
	{
		printf("pwd: ignoring non-option arguments\n");
	}
	// printf("%s\n", path);
	printf("%s\n", get_value(shell, "PWD"));
	return (0);
}
