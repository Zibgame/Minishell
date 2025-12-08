/* ************************************************************************** */ 	
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcadinot <zcadinot@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 12:19:24 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/08 12:41:17 by zcadinot         ###   ########.fr       */
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

	(void)shell;
	printf("exit\n");
	if (cmd->args[1] && (!is_numeric(cmd->args[1]) \
				|| !is_long_long(cmd->args[1] + (cmd->args[1][0] == '+' \
				||cmd->args[1][0] == '-'))))
	{
		printf("minishell: exit: %s: numeric argument required\n",
			cmd->args[1]);
		exit(2);
	}
	if (cmd->args[1] && cmd->args[2])
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	if (cmd->args[1])
	{
		code = ft_atoi(cmd->args[1]);
		exit((unsigned char)code);
	}
	exit(0);
}
