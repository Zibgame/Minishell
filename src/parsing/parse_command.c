/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 10:59:45 by aeherve           #+#    #+#             */
/*   Updated: 2026/01/05 23:21:35 by dadoune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	command_type(t_cmd	*cmd)
{
	int	status;

	if (cmd->quote)
		return (ARGUMENT);

	if (!ft_strncmp(cmd->name, "-", 2))
		return (PARSEERROR);
	if (is_builtins(cmd->name) != -1)
		return (is_builtins(cmd->name));
	status = is_redirect(cmd);
	if (status)
		return (status);
	status = is_pipe(cmd);
	if (status)
		return (status);
	return (ARGUMENT);
}

void	add_commands(t_cmd	**cmd, char **elems)
{
	int		i;
	int		old_size;

	if (elems)
	{
		i = -1;
		old_size = ft_cmdsize(*cmd);
		while (elems[++i])
		{
			ft_cmdadd_back(cmd, ft_cmdnew(ft_strdup(elems[i]), 0));
			ft_cmdlast(*cmd)->quote = get_token_quote(ft_cmdlast(*cmd)->name);
			ft_cmdlast(*cmd)->type = command_type(ft_cmdlast(*cmd));
			if (!(ft_cmdsize(*cmd) > old_size))
				return ;
			old_size = ft_cmdsize(*cmd);
		}
	}
}

void	remove_waste(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd && cmd->next)
	{
		if (cmd->next->type == TOREMOVE)
		{
			tmp = cmd->next;
			cmd->next = cmd->next->next;
			cmd->next->prev = cmd;
			ft_cmddelone(tmp);
		}
		cmd = cmd->next;
	}
}

t_cmd	*parse_command(char *line)
{
	char	**splitted_command;
	t_cmd	*cmd;

	splitted_command = tokenize_line(line);
	if (!splitted_command)
		return (NULL);
	cmd = ft_cmdnew(ft_strdup(splitted_command[0]), 0);
	cmd->quote = get_token_quote(splitted_command[0]);
	cmd->type = command_type(cmd);
	if (cmd)
		add_commands(&cmd, &splitted_command[1]);
	free_array(splitted_command);
	remove_waste(cmd);
	if (has_parse_error(cmd))
		return (NULL);
	return (cmd);
}
