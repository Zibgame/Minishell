/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:30:08 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/15 19:51:14 by dadoune          ###   ########.fr       */
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

int	finish(t_shell *shell)
{
	long long	code;

	code = 0;
	printf("exit\n");
	clean_command_free(shell);
	if (shell->cmd && shell->cmd->name && (!is_numeric(shell->cmd->name) \
		|| !is_long_long(shell->cmd->name)) + (shell->cmd->name[0] == '+' \
		|| shell->cmd->name[0] == '-'))
	{
		printf("minishell: exit: %s: numeric argument required\n",
			shell->cmd->name);
		code = 2;
	}
	else if (ft_cmdsize(shell->cmd) >= 2)
	{
		printf("minishell: exit: too many arguments\n");
		shell->last_return = code;
		return (1);
	}
	if (shell->cmd && shell->cmd->name)
		code = ft_atoi(shell->cmd->name);
	free_shell(shell);
	exit((unsigned char)code);
}
