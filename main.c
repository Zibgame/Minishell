/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 08:05:18 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/09 15:48:08 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	(void)argc;
	shell = create_shell_struct(envp);
	if (!shell)
		return (1);
	
	return (0);
}
