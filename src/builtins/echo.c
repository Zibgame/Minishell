/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 20:44:04 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/10 21:15:59 by dadoune          ###   ########.fr       */
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

int	echo(t_shell *shell)
{
	int		nl;
	t_cmd	*tmp;

	nl = 1;
	tmp = shell->cmd;
	while (tmp->type == 1 && is_valid_n(tmp->name))
	{
		nl = 0;
		tmp = tmp->next;
	}
	while (shell->cmd->type)
	{
	if (is_status_var(shell->cmd->args[i]))
		print_status(shell);
	else
		ft_putstr_fd(shell->cmd->args[i], 1);
		if (shell->cmd->args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (nl)
		write(1, "\n", 1);
	return (0);
}
