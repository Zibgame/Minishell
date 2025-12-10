/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 10:59:45 by aeherve           #+#    #+#             */
/*   Updated: 2025/12/10 19:40:50 by dadoune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	command_type(t_cmd	*cmd)
{
	int	status;
	
	if (is_builtins(cmd->name))
		return (is_builtins(cmd->name) - 1);
	status = is_redirect(cmd); 
	if (status)
		return (PARSEERROR * (status == 2) + REDIRECTION * (status == 1));
	status = is_pipe(cmd);
	if (status)
		return (status);
	else if (status == TOREMOVE || status == OPERATOR)
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
			ft_cmdlast(*cmd)->type = command_type(ft_cmdlast(*cmd));
			if (!(ft_cmdsize(*cmd) > old_size))
				return ;
			old_size = ft_cmdsize(*cmd);
		}
	}
}

t_cmd	*parse_command(char *line)
{
	
	char	**splitted_command;
	t_cmd	*cmd;
	
	splitted_command = ft_split(line, ' ');
	if (!splitted_command)
		return (NULL);
	cmd = ft_cmdnew(ft_strdup(splitted_command[0]), 0);
	cmd->type = command_type(cmd);
	if (cmd)
		add_commands(&cmd, &splitted_command[1]);
	free_array(splitted_command);
	return (cmd);
}
