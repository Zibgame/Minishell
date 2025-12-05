/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 09:20:15 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/05 10:31:08 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_shell	create_shell_struct(char **envp)
{
	t_shell	shell;

	shell.env = envp;
	return (shell);
}
