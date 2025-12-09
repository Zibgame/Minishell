/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcadinot <zcadinot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 20:44:04 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/09 11:53:34 by zcadinot         ###   ########.fr       */
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

static int	is_status_var(char *s)
{
	return (s && s[0] == '$' && s[1] == '?' && s[2] == '\0');
}

int	echo(t_cmd *cmd, t_shell *shell)
{
	int	i;
	int	nl;

	(void)shell;
	i = 1;
	nl = 1;
	while (cmd->args[i] && is_valid_n(cmd->args[i]))
	{
		nl = 0;
		i++;
	}
	while (cmd->args[i])
	{
    if (is_status_var(cmd->args[i]))
        print_status(shell);
    else
        ft_putstr_fd(cmd->args[i], 1);
		if (cmd->args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (nl)
		write(1, "\n", 1);
	return (0);
}
