/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 20:44:04 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/11 12:57:17 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_valid_n(char *s)
{
	int	i;

	if (!s || s[0] != '-' || s[1] != 'n')
		return (0);
	i = 2;
	while (s[i] == 'n')
		i++;
	return (s[i] == '\0');
}

int	echo(t_shell *shell)
{
	int		nl;

	nl = 1;
	while (shell->cmd->type == 1 && is_valid_n(shell->cmd->name))
	{
		nl = 0;
		shell->cmd = shell->cmd->next;
	}
	while (shell->cmd && shell->cmd->type == 4)
	{
		if (ft_strncmp(shell->cmd->name, "$?", 3))
			print_status(shell);
		else
			printf("%s", shell->cmd->name);
		if (shell->cmd->next && shell->cmd->next->type == 4)
			printf(" ");
		shell->cmd = shell->cmd->next;
	}
	if (nl)
		write(1, "\n", 1);
	return (0);
}
