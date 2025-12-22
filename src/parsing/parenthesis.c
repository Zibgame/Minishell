/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoune <dadoune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 11:24:19 by dadoune           #+#    #+#             */
/*   Updated: 2025/12/22 12:20:10 by dadoune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	remove_parenthesis(t_cmd *cmd, int last_parenth, char *dup, t_shell *shell)
{
	int	i;
	
	i = 0;
	while (cmd->name[++i])
	{
		if (last_parenth)
		{
			last_parenth = ((last_parenth == 39) * 39 * (cmd->name[i] != \
				39)) + ((last_parenth == 34) * 34 * (cmd->name[i] != 34));
			if (cmd->name[i] == '$' && last_parenth != 39 && (i == 0 || \
				(i > 0 && cmd->name[i] != '\\')))
				expansion(cmd, shell);
			else if (last_parenth)
				dup[ft_strlen(dup)] = cmd->name[i];
		}
		else
		{
			last_parenth = (39 * (cmd->name[i] == 39)) + \
			(34 * (cmd->name[i] == 34));
			if (!last_parenth)
				dup[ft_strlen(dup)] = cmd->name[i];
		}
	}
	return (last_parenth);
}

void	clear_parenthesis(t_cmd *last_added, t_shell *shell)
{
	int		last_parenthesis;
	int		unclosed_par;
	char	*dup;
	
	if (last_added && last_added->name && last_added->name[0])
	{
		dup = ft_calloc(ft_strlen(last_added->name) + 1, 1);
		if (last_added->name[0] == '$')
			expansion(last_added, shell);
		last_parenthesis = (39 * (last_added->name[0] == 39)) \
		+ (34 * (last_added->name[0] == 34));
		if (!last_parenthesis)
			dup[0] = last_added->name[0];
		unclosed_par = remove_parenthesis(last_added, last_parenthesis, dup,
			shell);
		free(last_added->name);
		last_added->name = dup;
		if (unclosed_par)
			printf("uncompleted parenthesis, pls open an heredoc\n");
	}
}
