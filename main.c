/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcadinot <zcadinot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 08:05:18 by zcadinot          #+#    #+#             */
/*   Updated: 2026/01/15 15:16:39 by zcadinot         ###   ########.fr       */
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
		printf("prev: %p\n", cmd->prev); 
		printf("next: %p\n", cmd->next); 
		printf("-------------------------------------------\n"); 
		cmd = cmd->next; 
	} 
} 

// int	main(int argc, char **argv, char **envp)
// {
// 	int		i;
// 	char	*bufr;
// 	t_shell	*shell;

// 	(void)argc;
// 	shell = create_shell_struct(envp);
// 	if (!shell)
// 		return (1);
// 	bufr = ft_calloc(500, 1);
// 	i = 0;
// 	while (argv[i])
// 	{
// 		bufr = join_and_free(bufr, argv[i++]);
// 		if (argv[i])
// 			bufr = join_and_free(bufr, " ");
// 	}
// 	shell->cmd = parse_command(bufr);
// 	free(bufr);c
// 	display_list(shell->cmd);
// 	free_shell(shell);
// 	return (0);
// }

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
