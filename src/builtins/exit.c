/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:30:08 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/08 21:28:08 by dadoune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_numeric(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	is_long_long(char *str)
{
	long long	nb;
	long long	prev;
	int			i;

	nb = 0;
	i = 0;
	while (str[i])
	{
		prev = nb;
		nb = nb * 10 + (str[i] - '0');
		if (nb / 10 != prev)
			return (0);
		i++;
	}
	return (1);
}

int	finish(t_cmd *cmd, t_shell *shell)
{
	long long	code;

	code = 0;
	shell->actual_command = cmd;
	printf("exit\n");
	if (cmd->args[1] && (!is_numeric(cmd->args[1]) \
			|| !is_long_long(cmd->args[1] + (cmd->args[1][0] == '+' \
			|| cmd->args[1][0] == '-'))))
	{
		printf("minishell: exit: %s: numeric argument required\n",
			cmd->args[1]);
		code = 2;
	}
	else if (cmd->args[1] && cmd->args[2])
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	if (cmd->args[1])
		code = ft_atoi(cmd->args[1]);
	free_shell(shell);
	exit((unsigned char)code);
}

