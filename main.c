/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 08:05:18 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/17 19:39:39 by dadoune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	display_list(t_cmd	*cmd) 
{
	while (cmd) 
	{ 
		printf("-------------------------------------------\n"); 
		printf("name: %s type: %d\n", cmd->name, cmd->type); 
		printf("adress: %p\n", cmd); 
		printf("quote: %c\n", cmd->quote); 
		printf("\n");
		if (cmd->redirs)
			printf("redirs:\n");
		while (cmd->redirs)
		{
			printf("\t%s\n", cmd->redirs->target);
			cmd->redirs = cmd->redirs->next;
		}
		printf("prev: %p\n", cmd->prev); 
		printf("next: %p\n", cmd->next); 
		printf("-------------------------------------------\n"); 
		cmd = cmd->next; 
	} 
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	
	shell = create_shell_struct(envp);
	if (!shell)
		return (1);
	start_shell(shell);
	return (0);
}
