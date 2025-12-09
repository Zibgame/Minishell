/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_next_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:05:03 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/09 20:25:02 by dadoune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_cmd	extract_next_cmd(t_cmd *cmd)
{
	t_cmd	new;
	// char	**new_args;

	new.name = NULL;
	new.type = 0;
	if (!cmd || !cmd->type)
		return (new);
	// new_args = copy_args_next(cmd->type);
	// if (!new_args)
	// 	return (new);
	// new.name = cmd->name;
	// new.type = new_args;
	return (new);
}
