/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcadinot <zcadinot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 20:44:04 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/09 16:37:42 by zcadinot         ###   ########.fr       */
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

static int	print_variable(char *args, t_shell *shell)
{
	if (get_value(shell ,&args[1]))
		return (printf("%s",get_value(shell, &args[1])));
	if (!ft_strncmp(args, "$?", 3))
    return (print_status(shell));
	return (0);
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
		if (!print_variable(cmd->args[i], shell))
    	ft_putstr_fd(cmd->args[i], 1);
		if (cmd->args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (nl)
		printf("\n");
	return (0);
}
