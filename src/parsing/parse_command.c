/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 10:59:45 by aeherve           #+#    #+#             */
/*   Updated: 2025/12/09 17:52:47 by aeherve          ###   ########.fr       */
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
	
}

void	add_commands(t_cmd	**cmd, char **elems)
{
	int		i;
	int		old_size;
	t_cmd	*tmp;

	i = -1;
	old_size = 1;
	while (elems[++i])
	{
		ft_cmdadd_back(cmd, ft_cmdnew(elems[i], 0));
		ft_cmdlast(cmd)->type = command_type(ft_cmdlast(cmd));
		if (!(ft_cmdsize(*cmd) > old_size))
			return ;
		old_size = ft_cmdsize(*cmd);
	}
}

t_cmd	*parse_command(char *line)
{
	
	char	**splitted_command;
	t_cmd	*cmd;
	
	splitted_command = ft_split(line, ' ');
	if (!splitted_command)
		return (NULL);
	cmd = ft_cmdnew(splitted_command[0], command_type(cmd));
	if (cmd)
		add_commands(&cmd, &splitted_command[1]);
	return (cmd);
}
