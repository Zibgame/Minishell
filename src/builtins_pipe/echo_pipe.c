/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 10:58:30 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/18 13:39:12 by aeherve          ###   ########.fr       */
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

int	echo_pipe(t_cmd *cmd)
{
	int	nl;

	nl = 1;
	cmd = cmd->next;
	while (cmd && is_valid_n(cmd->name))
	{
		nl = 0;
		cmd = cmd->next;
	}
	while (cmd && (cmd->type == ARGUMENT || cmd->type == OPTION))
	{
		ft_putstr_fd(cmd->name, STDOUT_FILENO);
		if (cmd->next && (cmd->next->type == ARGUMENT
				|| cmd->next->type == OPTION))
			write(1, " ", 1);
		cmd = cmd->next;
	}
	if (nl)
		write(1, "\n", 1);
	return (0);
}
