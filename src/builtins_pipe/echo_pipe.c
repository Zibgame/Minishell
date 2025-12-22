/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 10:58:30 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/22 16:44:49 by zcadinot         ###   ########.fr       */
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

static void	print_variable_pipe(t_shell *shell, char *name)
{
	t_var_list	*tmp;

	tmp = shell->envp;
	while (tmp)
	{
		if (!ft_strncmp(name + 1, tmp->name, ft_strlen(tmp->name) + 1))
		{
			ft_putstr_fd(tmp->value, STDOUT_FILENO);
			return ;
		}
		tmp = tmp->next;
	}
}

static void	display_arg_pipe(t_shell *shell, t_cmd *cmd)
{
	if (!ft_strncmp(cmd->name, "$?", 3))
		ft_putnbr_fd(shell->last_return, STDOUT_FILENO);
	else if (cmd->name[0] == '$')
		print_variable_pipe(shell, cmd->name);
	else
		ft_putstr_fd(cmd->name, STDOUT_FILENO);
}

int	echo_pipe(t_shell *shell, t_cmd *cmd)
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
		display_arg_pipe(shell, cmd);
		if (cmd->next && (cmd->next->type == ARGUMENT
				|| cmd->next->type == OPTION))
			write(1, " ", 1);
		cmd = cmd->next;
	}
	if (nl)
		write(1, "\n", 1);
	return (0);
}
