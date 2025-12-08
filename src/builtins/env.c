/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 09:41:46 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/08 11:12:02 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env(t_cmd *cmd, t_shell *shell)
{
	t_var_list	*vars;

	(void)cmd;
	vars = shell->envp;
	while (vars)
	{
		if (vars->value)
		{
			printf("%s=%s\n", vars->name, vars->value);
		}
		vars = vars->next;
	}
}
