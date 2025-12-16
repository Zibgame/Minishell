/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_next_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:05:03 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/16 14:05:40 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_cmd	extract_next_cmd(t_cmd *cmd)
{
	t_cmd	new;

	new.name = NULL;
	new.type = 0;
	if (!cmd || !cmd->type)
		return (new);
	return (new);
}
