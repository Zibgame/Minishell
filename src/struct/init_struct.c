/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcadinot <zcadinot@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 09:20:15 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/02 09:22:03 by zcadinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	create_shell_struct(char **envp)
{
	t_shell	shell;

	shell.env = envp;
	return (shell);
}
