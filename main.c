/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeherve <aeherve@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 08:05:18 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/08 16:46:02 by aeherve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int	i;
	t_shell	*shell;

	(void)argc;
	(void)argv;
	i = 0;
	while (envp[i])
		printf("|%s|\n", envp[i++]);	
	shell = create_shell_struct(envp);
	if (!shell)
		return (1);
	start_shell(shell);
	return (0);
}
