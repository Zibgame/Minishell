/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:30:08 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/05 22:55:17 by dadoune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static int	numeric_argument_return(const char *str)
// {
// 	if ()
// 	return (2);
// 	return (156);
// }

static int	is_str_numeric(const char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-' || str[i] == '\"' || str[i] == '\'')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9') && \
		(str[i] != '\"' || str[i] == '\''))
			return (0);
		i++;
	}
	return (1);
}

static int	parse_ll(const char *str, long long *out)
{
	int			i;
	int			sign;
	long long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == '+' || str[i] == '-' || str[i] == '\"' || str[i] == '\'')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		if (str[i] != '\"' && str[i] != '\'')
		{
			if (res > (LLONG_MAX - (str[i] - '0')) / 10)
				return (0);
			res = res * 10 + (str[i] - '0');
		}
		i++;
	}
	*out = res * sign;
	return (1);
}

int	finish(t_shell *shell)
{
	long long	code;

	code = 0;
	printf("exit\n");
	clean_command_free(shell);
	if (shell->cmd && shell->cmd->name)
	{
		if (!is_str_numeric(shell->cmd->name)
			|| !parse_ll(shell->cmd->name, &code))
		{
			ft_printf_fd("minishell: exit: %s: numeric argument required\n", 2,
				shell->cmd->name);
			clean_command_free(shell);
			free_shell(shell);
			exit(2);
		}
		if (ft_cmdsize(shell->cmd) >= 2)
		{
			ft_printf_fd("minishell: exit: too many arguments\n", 2);
			shell->last_return = 1;
			return (1);
		}
	}
	free_shell(shell);
	exit((unsigned char)code);
}
