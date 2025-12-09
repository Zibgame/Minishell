/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_next_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:05:03 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/09 15:09:53 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_cmd	extract_next_cmd(t_cmd *cmd)
{
	t_cmd	new;
	char	**new_args;

	new.name = NULL;
	new.type = NULL;
	if (!cmd || !cmd->type)
		return (new);
	new_args = copy_args_next(cmd->type);
	if (!new_args)
		return (new);
	new.name = cmd->name;
	new.type = new_args;
	return (new);
}
