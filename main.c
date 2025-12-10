/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 08:05:18 by zcadinot          #+#    #+#             */
/*   Updated: 2025/12/10 17:05:47 by dadoune          ###   ########.fr       */
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
		printf("\n");
		printf("prev: %p\n", cmd->prev);
		printf("next: %p\n", cmd->next);
		printf("-------------------------------------------\n");
		cmd = cmd->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	char	*bufr;
	t_shell	*shell;

	(void)argc;
	shell = create_shell_struct(envp);
	if (!shell)
		return (1);
	bufr = ft_calloc(500, 1);
	i = 0;
	while (argv[i])
	{
		bufr = join_and_free(bufr, argv[i++]);
		if (argv[i])
			bufr = join_and_free(bufr, " ");
	}
	shell->cmd = parse_command(bufr);
	free(bufr);
	display_list(shell->cmd);
	free_shell(shell);
	return (0);
}
