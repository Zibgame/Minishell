/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 17:00:18 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/15 19:36:48 by dadoune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pwd(t_shell *shell)
{
	char	buff[2048];
	char	*path;

	path = getcwd(buff, 2048);
	if (!path)
	{
		printf("pwd: error retrieving current directory\n");
		shell->last_return = 1;
		return (1);
	}
	printf("%s\n", path);
	clean_command_free(shell);
	shell->last_return = 0;
	return (0);
}
